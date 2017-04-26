#include <QDirIterator>
#include <QFileInfo>
#include <QFile>
#include <QDebug>
#include <QDateTime>

#include "HandHistory.h"

HandHistory::HandHistory() :
  m_lastHandId(0)
{

}

void HandHistory::parseFolder()
{
  QDirIterator it("/Users/Ulle/Library/Application Support/PokerStarsEU/HandHistory/UnlimitedDep");

  while (it.hasNext())
  {
    QString fileName = it.next();

    if (!fileName.endsWith(".txt"))
    {
      continue;
    }

    QFileInfo fileInfo(fileName);

    QDateTime lastModified = fileInfo.lastModified();

    if (lastModified == m_filesLastModfied[fileName])
    {
      continue;
    }

    m_filesLastModfied[fileName] = lastModified;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      qDebug() << "unable to open file";
      continue;
    }

    QString fileContent = file.readAll();

    QStringList fileHands = fileContent.split("\n\n\n\n");

    for (auto it = fileHands.begin(); it != fileHands.end(); it++)
    {
      if (it->isEmpty())
      {
        // special case in end of file
        continue;
      }

      Hand hand(it->split('\n'));
      m_hands[hand.id()] = hand;
    }
  }

  int numberOfHands = m_hands.keys().length();

  m_information = QString("%1 hands counted\n\n").arg(numberOfHands);

  if (numberOfHands > 0)
  {
    QMap<QString, int> players = m_hands.last().m_players;

    for (auto it = players.begin(); it != players.end(); ++it)
    {
      if (it.key() == "UnlimitedDep")
      {
        continue;
      }
      m_information.append(playerInformation(it.key()));
    }

    m_information.append("\n\nInformation about last hand:\n");
    m_information.append(m_hands.last().information());
    m_lastHandId = m_hands.last().id();
  }
}

bool HandHistory::contains(quint64 id)
{
  return m_hands.contains(id);
}

QString HandHistory::information()
{
  return m_information;
}

quint64 HandHistory::lastHandId()
{
  return m_lastHandId;
}

QString HandHistory::handInformation(quint64 id)
{
  if (!m_hands.contains(id))
  {
    return QString();
  }

  return m_hands[id].information();
}

QString HandHistory::playerInformation(const QString &playerName)
{
  QString info = QString("\ninfo about %1\n").arg(playerName);
  int number = 0;
  int numberOfActions = 0;
  int numberPreFlopBet = 0;
  int numberCall = 0;
  int numberRaise = 0;
  int numberFold = 0;
  int numberCheck = 0;
  int numberBet = 0;

  for (auto it = m_hands.begin(); it != m_hands.end(); ++it)
  {
    if (it.value().m_players.keys().contains(playerName))
    {
      number++;

      QList<Action> actions = it.value().m_actions;

      bool incremented = false;
      for (auto it2 = actions.begin(); it2 != actions.end(); ++it2)
      {
        if (it2->m_player == playerName)
        {
          numberOfActions++;

          if (it2->m_phase == PreFlop && !incremented && !(it2->m_type == Action::Fold || it2->m_type == Action::Check))
          {
            numberPreFlopBet++;
            incremented = true;
          }

          if (it2->m_type == Action::Fold)
          {
            numberFold++;
          }
          else if (it2->m_type == Action::Call)
          {
            numberCall++;
          }
          else if (it2->m_type == Action::Raise || it2->m_type == Action::CheckRaise || it2->m_type == Action::ReRaise)
          {
            numberRaise++;
          }
          else if (it2->m_type == Action::Check)
          {
            numberCheck++;
          }
          else if (it2->m_type == Action::Bet)
          {
            numberBet++;
          }
        }


      }
    }
  }

  info.append(QString("%1 hands played together\n").arg(number));


  info.append(QString("%1 % folds\n").arg(numberFold * 100.0 / numberOfActions));
  info.append(QString("%1 % calls\n").arg(numberCall * 100.0 / numberOfActions));
  info.append(QString("%1 % check\n").arg(numberCheck * 100.0 / numberOfActions));
  info.append(QString("%1 % bet\n").arg(numberBet * 100.0 / numberOfActions));
  info.append(QString("%1 % raise\n").arg(numberRaise * 100.0 / numberOfActions));

  double aggressionIndex = 0.0;

  int passiveActions = numberCall + numberCheck;

  if (passiveActions != 0)
  {
    aggressionIndex = (numberBet + numberRaise) * 1.0 / passiveActions;
  }

  info.append(QString("aggression index %1\n").arg(aggressionIndex));
  info.append(QString("%1 % hands played\n").arg(numberPreFlopBet * 100.0 / number));



  return info;
}
