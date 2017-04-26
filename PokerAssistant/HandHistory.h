#ifndef HANDHISTORY_H
#define HANDHISTORY_H

#include <QDateTime>
#include <QString>
#include <QMap>

#include "Hand.h"

class HandHistory
{
public:
  HandHistory();

  void parseFolder();

  bool contains(quint64 id);

  QString information();
  quint64 lastHandId();

  QString handInformation(quint64 id);
  QString playerInformation(const QString& playerName);

private:
  QString m_information;
  QMap<QString, QDateTime> m_filesLastModfied;
  QMap<quint64, Hand> m_hands;
  quint64 m_lastHandId;
};

#endif // HANDHISTORY_H
