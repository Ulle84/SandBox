#ifndef POSSIBLEMOVES_H
#define POSSIBLEMOVES_H

#include "PlayingField.h"
#include "FlingMove.h"
#include "GameHistory.h"

class PossibleMoves
{
public:
  PossibleMoves(PlayingField* playingField, FlingMove flingMove, GameHistory gameHistory);
  PlayingField* playingField;
  FlingMove flingMove;
  GameHistory gameHistory;
  void play();
};

#endif // POSSIBLEMOVES_H
