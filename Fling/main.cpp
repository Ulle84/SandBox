#include <QCoreApplication>
#include <PlayingField.h>
#include <PossibleMoves.h>

#include <iostream>

int main(int argc, char* argv[])
{
  bool debug = true;

  QCoreApplication a(argc, argv);

  int argumentCount = 2;

  if (argc < argumentCount)
  {
    std::cout << "argument count must be: " << argumentCount << std::endl;
    return 0;
  }

  QString fileName = argv[1];

  PlayingField* playingField = new PlayingField(fileName);
  GameHistory gameHistory;

  std::cout << "count of flings: " << playingField->flings->count() << std::endl;
  QList<PossibleMoves> possibleMoves;
  bool firstRun = true;
  //do
  {
    // save playingField
    if (firstRun)
    {
      firstRun = false;
    }
    else
    {
      playingField = possibleMoves.last().playingField;
    }

    // find possible moving directions
    for (int i = 0; i < playingField->flings->count() - 1; i++)
    {
      for (int j = i + 1; j < playingField->flings->count(); j++)
      {
        // check if x is the same
        if (playingField->flings->at(i).x == playingField->flings->at(j).x)
        {
          int distance = abs(playingField->flings->at(i).y - playingField->flings->at(j).y);
          std::cout << "distance: " << distance << std::endl;

          if (distance < 2)
          {
            continue;
          }

          FlingMove flingMove1(playingField->flings->at(i), UNDEFINED);
          FlingMove flingMove2(playingField->flings->at(j), UNDEFINED);

          if (playingField->flings->at(i).y < playingField->flings->at(j).y)
          {
            flingMove1.direction = UP;
            flingMove2.direction = DOWN;
          }
          else
          {
            flingMove1.direction = DOWN;
            flingMove2.direction = UP;
          }

          PossibleMoves possibleMove1(playingField, flingMove1, gameHistory);
          PossibleMoves possibleMove2(playingField, flingMove2, gameHistory);
          possibleMoves.append(possibleMove1);
          possibleMoves.append(possibleMove2);

          if (debug)
          {
            possibleMove1.flingMove.print();
            possibleMove2.flingMove.print();
          }
        }

        // check if y is the same
        if (playingField->flings->at(i).y == playingField->flings->at(j).y)
        {
          int distance = abs(playingField->flings->at(i).x - playingField->flings->at(j).x);
          std::cout << "distance: " << distance << std::endl;

          if (distance < 2)
          {
            continue;
          }

          FlingMove flingMove1(playingField->flings->at(i), UNDEFINED);
          FlingMove flingMove2(playingField->flings->at(j), UNDEFINED);

          if (playingField->flings->at(i).x < playingField->flings->at(j).x)
          {
            flingMove1.direction = RIGHT;
            flingMove2.direction = LEFT;
          }
          else
          {
            flingMove1.direction = LEFT;
            flingMove2.direction = RIGHT;
          }

          PossibleMoves possibleMove1(playingField, flingMove1, gameHistory);
          PossibleMoves possibleMove2(playingField, flingMove2, gameHistory);
          possibleMoves.append(possibleMove1);
          possibleMoves.append(possibleMove2);

          if (debug)
          {
            possibleMove1.flingMove.print();
            possibleMove2.flingMove.print();
          }
        }
      }
    }

    // play last possible move
    if (possibleMoves.count() > 1)
    {
      possibleMoves.last().play();
    }

    // if no more movement possible
    if (possibleMoves.last().playingField->flings->length() == 1)
    {
      // found a solution
      std::cout << "found a solution" << std::endl;
      possibleMoves.removeLast();
    }
  }
  //while (possibleMoves.length() > 0);

  return a.exec();
}
