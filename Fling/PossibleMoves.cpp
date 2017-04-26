#include "PossibleMoves.h"
#include <QList>

#include <iostream>

PossibleMoves::PossibleMoves(PlayingField* playingField, FlingMove flingMove, GameHistory gameHistory)
  : playingField(playingField), flingMove(flingMove), gameHistory(gameHistory)
{
}

void PossibleMoves::play()
{
  // find fling in playingField and remove
  // ToDo optimize data-structure, so the position is inside the data-structure
  unsigned int x = 0;
  unsigned int y = 0;

  for (int i = 0; i < playingField->flings->length(); i++)
  {
    if (playingField->flings->at(i).x == flingMove.fling.x && playingField->flings->at(i).y == flingMove.fling.y)
    {
      x = flingMove.fling.x;
      y = flingMove.fling.y;
      playingField->flings->removeAt(i);
      break;
    }
  }

  switch (flingMove.direction)
  {
  case UP:
    std::cout << "move up" << std::endl;

    for (int i = 0; i < playingField->flings->length(); i++)
    {
      if (playingField->flings->at(i).y < y)
      {
        playingField->flings->value(i).setY(y - 1); //.setY(y - 1);
      }
    }

    break;

  case DOWN:
    std::cout << "move down" << std::endl;

    for (int i = 0; i < playingField->flings->length(); i++)
    {
      if (playingField->flings->at(i).y < y)
      {
        playingField->flings->value(i).setY(y + 1);
      }
    }

    break;

  case LEFT:
    std::cout << "move left" << std::endl;

    for (int i = 0; i < playingField->flings->length(); i++)
    {
      if (playingField->flings->at(i).x < x)
      {
        playingField->flings->value(i).setX(x + 1);
      }
    }

    break;

  case RIGHT:
    std::cout << "move right" << std::endl;

    for (int i = 0; i < playingField->flings->length(); i++)
    {
      if (playingField->flings->at(i).x > x)
      {
        playingField->flings->value(i).setX(x - 1);
      }
    }

    break;
  }

  gameHistory.history->append(flingMove);
}
