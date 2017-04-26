#include <QDebug>

#include "Hand.h"

Hand::Hand()
{

}

Hand::Hand(const QStringList& information)
{
  m_information = information;
  parseInformation();
  analyzeActions();
}

QString Hand::information()
{
  QString information;
  information.append(QString("ID: %1\n").arg(m_id));
  information.append(m_dateTime.toString("yyyy-MM-dd hh:mm:ss\n"));
  information.append(QString("small blind: %1\n").arg(m_smallBlindValue));
  information.append(QString("big blind: %1\n").arg(m_bigBlindValue));

  information.append(QString("Own cards:"));

  for (auto it = m_ownCards.begin(); it != m_ownCards.end(); ++it)
  {
    information.append(" ");
    information.append(it->abbreviation());
  }

  information.append(QString("\ntable name: %1\n").arg(m_tableName));
  information.append(QString("dealer position: %1\n").arg(m_dealerPosition));
  information.append(QString("small blind position: %1\n").arg(m_smallBlindPosition));
  information.append(QString("big blind position: %1\n").arg(m_bigBlindPosition));

  information.append("players:\n");
  for (auto it = m_players.begin(); it != m_players.end(); it++)
  {
    information.append(QString("%1 on position: %2\n").arg(it.key()).arg(it.value()));
  }

  information.append(QString("\nPot: %1\n").arg(m_pot));
  information.append(QString("Rake: %1\n\n").arg(m_rake));

  double totalPotWinnings = 0.0;
  for (auto it = m_potWinnings.begin(); it != m_potWinnings.end(); ++it)
  {
    information.append(QString("%1 wins %2\n").arg(it.key()).arg(it.value()));
    totalPotWinnings += it.value();
  }

  // some checks
  if (totalPotWinnings != (m_pot - m_rake))
  {
    information.append("\n ERROR: totalPotWinnings != (m_pot - m_rake)\n");
  }

  information.append("\nActions:\n");

  for (auto it = m_actions.begin(); it != m_actions.end(); ++it)
  {
    information.append(it->toString());
  }

  information.append("\n");
  information.append(m_information.join("\n"));

  return information;
}

quint64 Hand::id()
{
  return m_id;
}

void Hand::analyzeActions()
{
  // TODO fill QMap<QString, double> m_potContribution;
}

QString Hand::stringBetween(const QString& info, const QString& left, const QString& right)
{
  int start = info.indexOf(left);

  if (start < 0)
  {
    return QString();
  }

  start += left.length();

  int end = info.indexOf(right, start);

  if (end < 0)
  {
    return QString();
  }

  return info.mid(start, end - start);
}

QString Hand::stringStart(const QString &info, const QString &end)
{
  int stop = info.indexOf(end);

  if (stop < 0)
  {
    return QString();
  }

  return info.left(stop);
}

void Hand::parseInformation()
{
  Phase phase = BeforeHand;

  for (auto it = m_information.begin(); it != m_information.end(); it++)
  {
    if (it->startsWith("***"))
    {
      if (it->startsWith("*** HOLE CARDS ***"))
      {
        phase = PreFlop;
      }
      else if (it->startsWith("*** FLOP ***"))
      {
        phase = Flop;
      }
      else if (it->startsWith("*** TURN ***"))
      {
        phase = Turn;
      }
      else if (it->startsWith("*** RIVER ***"))
      {
        phase = River;
      }
      else if (it->startsWith("*** SHOWDOWN ***"))
      {
        phase = Showdown;
      }
      else if (it->startsWith("*** ZUSAMMENFASSUNG ***"))
      {
        phase = Summary;
      }
      continue;
    }

    if (phase == BeforeHand)
    {
      if (it == m_information.begin())
      {
        parseId(*it);
        parseDateTime(*it);
        parseBlinds(*it);
      }
      else if (it->startsWith("Tisch"))
      {
        parseTableName(*it);
        parseDealerPosition(*it);
      }
      else if (it->startsWith("Platz"))
      {
        parsePlayerPlace(*it);
      }
      else if (it->contains("Small Blind"))
      {
        parseSmallBlindPosition(*it);
      }
      else if (it->contains("Big Blind"))
      {
        parseBigBlindPosition(*it);
      }
    }

    if (phase == PreFlop)
    {
      if (it->contains("gewinnt"))
      {
        parseWinning(*it);
      }
      else if (it->contains("bekommt"))
      {
        parseOwnCards(*it);
      }
      else
      {
        parseAndAppendAction(*it, PreFlop, m_actions);
      }
    }

    if (phase == Flop || phase == Turn || phase == River)
    {
      if (it->contains("gewinnt"))
      {
        parseWinning(*it);
      }
      else
      {
        parseAndAppendAction(*it, phase, m_actions);
      }
    }

    if (phase == Showdown)
    {
      if (it->contains("gewinnt"))
      {
        parseWinning(*it);
      }
    }

    if (phase == Summary)
    {
      if (it->startsWith("Pot gesamt:"))
      {
        parsePotAndRake(*it);
      }
    }
  }
}

void Hand::parseId(const QString &info)
{
  if (m_information.length() < 1)
  {
    return;
  }

  QString idOffset = "PokerStars Hand Nr. ";

  if (!info.startsWith(idOffset))
  {
    return;
  }

  int index = info.indexOf(':', idOffset.length());

  if (index < 0)
  {
    return;
  }

  m_id = info.mid(idOffset.size(), index - idOffset.size()).toULongLong();
}

void Hand::parseDateTime(const QString &info)
{
  int start = info.indexOf('-') + 2;

  if (start < 0)
  {
    return;
  }

  QString dateTime = info.mid(start, 19);
  m_dateTime = QDateTime::fromString(dateTime, "dd.MM.yyyy hh:mm:ss");
}

void Hand::parseOwnCards(const QString &info)
{
  QString cards = stringBetween(info, "[", "]");
  QStringList cardList = cards.split(' ');

  for (auto it = cardList.begin(); it != cardList.end(); it++)
  {
    Card card(*it);
    m_ownCards.append(card);
  }
}

void Hand::parseTableName(const QString &info)
{
  m_tableName = stringBetween(info, "\'", "\'");
}

void Hand::parseDealerPosition(const QString &info)
{
  m_dealerPosition = stringBetween(info, "#", " ").toInt();
}

void Hand::parseSmallBlindPosition(const QString &info)
{
  m_smallBlindPosition = m_players[stringStart(info, ": setzt")];
}

void Hand::parseBigBlindPosition(const QString &info)
{
  m_bigBlindPosition = m_players[stringStart(info, ": setzt")];
}

void Hand::parsePlayerPlace(const QString &info)
{
  int place = stringBetween(info, "Platz ", ":").toInt();
  QString name = stringBetween(info, ": ", " (");
  m_players[name] = place;
}

QString Hand::parsePlayerName(const QString &info)
{
  return stringStart(info, ": ");
}

void Hand::parseAndAppendAction(const QString &info, Phase phase, QList<Action> &actions)
{

  Action::Type type = Action::Undefined;
  double m_value;

  if (info.contains("erhöht"))
  {
    // TODO CheckRaise, ReRaise -> analyse actions
    type = Action::Raise;
  }
  else if (info.contains("passt"))
  {
    type = Action::Fold;
  }
  else if (info.contains("geht mit"))
  {
    type = Action::Call;
  }
  else if (info.contains("setzt $"))
  {
    type = Action::Bet;
  }
  else if (info.contains("checkt"))
  {
    type = Action::Check;
  }

  if (type != Action::Undefined)
  {
    QString playerName = parsePlayerName(info);

    double value = 0.0;

    if (type == Action::Raise || type == Action::CheckRaise || type == Action::ReRaise)
    {
      value = parseRaiseValue(info);
    }
    else if(type == Action::Bet)
    {
      value = parseBetValue(info);
    }

    actions.append(Action(phase, playerName, type, value));
  }
}

double Hand::parseRaiseValue(const QString &info)
{
  return stringBetween(info, "erhöht $", " auf ").toDouble();
}

double Hand::parseBetValue(const QString &info)
{
  return info.right(info.size() - info.indexOf('$') - 1).split(" ").at(0).toDouble();
}

void Hand::parsePotAndRake(const QString &info)
{
  m_pot = stringBetween(info, "Pot gesamt: $", " ").toDouble();
  m_rake = stringBetween(info, "Rake: $", " ").toDouble();
}

void Hand::parseWinning(const QString &info)
{
  double value = stringBetween(info, "gewinnt $", " aus dem  Pot").toDouble();
  QString player = stringStart(info, " gewinnt");
  m_potWinnings[player] = value;
}

void Hand::parseBlinds(const QString &info)
{
  m_smallBlindValue = stringBetween(info, "($", "/").toDouble();
  m_bigBlindValue = stringBetween(info, "/$", " USD)").toDouble();
}
