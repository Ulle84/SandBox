#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include <QList>

#include "FlingMove.h"

class GameHistory
{
public:
  GameHistory();
  QList<FlingMove>* history;
};

#endif // GAMEHISTORY_H
