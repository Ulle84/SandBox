#ifndef HAND_H
#define HAND_H

#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QChar>

#include "Action.h"
#include "Card.h"
#include "Phase.h"

class Hand
{
public:
  Hand();
  Hand(const QStringList& information);

  QString information();
  quint64 id();

private:
  void analyzeActions();

  QString stringBetween(const QString& info, const QString& left, const QString& right);
  QString stringStart(const QString& info, const QString& end);

  void parseInformation();
  void parseId(const QString& info);
  void parseDateTime(const QString& info);
  void parseOwnCards(const QString& info);
  void parseTableName(const QString& info);
  void parseDealerPosition(const QString& info);
  void parseSmallBlindPosition(const QString& info);
  void parseBigBlindPosition(const QString& info);
  void parsePlayerPlace(const QString& info);
  QString parsePlayerName(const QString& info);
  void parseAndAppendAction(const QString& info, Phase phase, QList<Action>& actions);
  double parseRaiseValue(const QString& info);
  double parseBetValue(const QString& info);
  void parsePotAndRake(const QString& info);
  void parseWinning(const QString& info);
  void parseBlinds(const QString& info);

  quint64 m_id;
  QStringList m_information;
  QDateTime m_dateTime;
  QString m_tableName;
  int m_dealerPosition;
  int m_smallBlindPosition;
  int m_bigBlindPosition;

  double m_smallBlindValue;
  double m_bigBlindValue;
  double m_rake;
  double m_pot;

  QList<Card> m_ownCards;
  QList<Card> m_boardCards;

  QMap<QString, int> m_players; // todo change int to enum -> Dealer, SmallBlind, BigBlind, 4thPos, ...
  QMap<QString, double> m_potContribution;
  QMap<QString, double> m_potWinnings;

  QList<Action> m_actions;

  friend class HandHistory;
};

#endif // HAND_H
