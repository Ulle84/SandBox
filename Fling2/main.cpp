/* ToDo
- anstatt der notAllowedPossibleMoves-Liste: Schleifenzähler in den beiden for-Schleifen manipulieren -> wenn eine Bewegung gefunden wurde, dann kann zum nächsten Fling gesprungen werden
*/

#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QList>
#include <QPoint>
#include <QVariant>
#include <QPair>

#include <iostream>
#include <list>
#include <utility>

#ifdef Q_WS_WIN
#include "Windows.h"
#endif

using namespace std;

const string dashedLine = "--------------------------------------------------------------------------------";

enum Direction {UNDEFINED, UP, RIGHT, DOWN, LEFT};

void printDirection(Direction direction)
{
  switch (direction)
  {
  case UP:
    std::cout << "up";
    break;

  case DOWN:
    std::cout << "down";
    break;

  case RIGHT:
    std::cout << "right";
    break;

  case LEFT:
    std::cout << "left";
    break;

  default:
    cout << "undefined" << endl;
  }
}

QList<QPoint> createGameField(QString fileName, bool debug)
{
  QList<QPoint> flings;

  if (debug)
  {
    cout << "read file: " << fileName.toStdString().c_str() << endl;
  }

  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly))
  {
    cout << "could not open file" << endl;
    return flings;
  }

  while (!file.atEnd())
  {
    QString line = file.readLine();
    QStringList numbers = line.split(" ");

    if (numbers.count() < 2)
    {
      cout << "stop reading" << endl;
      break;
    }

    int x = QVariant(numbers.at(0)).toInt();
    int y = QVariant(numbers.at(1)).toInt();
    QPoint fling(x, y);
    flings.append(fling);
  }

  return flings;
}

void printFlings(QList<QPoint> flings)
{
  cout << "List of Flings (total " << flings.length() << "):" << endl;

  for (int i = 0; i < flings.length(); i++)
  {
    cout << "fling x: " << flings.value(i).x() << " y: " << flings.value(i).y() << endl;
  }

  cout << dashedLine.c_str() << endl;
}

class possibleMove
{
public:
  QList<QPoint> gameField;
  int flingNumber;
  Direction moveDirection;
  QList<QPair<QPoint, Direction> > history;
};

inline bool operator==(possibleMove pM1, possibleMove pM2)
{
  return pM1.flingNumber == pM2.flingNumber && pM1.gameField == pM2.gameField && pM1.moveDirection == pM2.moveDirection;
}

void moveFling(possibleMove& myPossibleMove, bool debug)
{
  QPair<QPoint, Direction> pair(myPossibleMove.gameField.value(myPossibleMove.flingNumber), myPossibleMove.moveDirection);
  myPossibleMove.history.append(pair);

  int x = myPossibleMove.gameField.at(myPossibleMove.flingNumber).x();
  int y = myPossibleMove.gameField.at(myPossibleMove.flingNumber).y();

  if (debug)
  {
    cout << "gameField before move: " << endl;
    printFlings(myPossibleMove.gameField);
    cout << "moving fling nr. " << myPossibleMove.flingNumber;
    cout << " (x: " << x << " y: " << y << ") ";
    printDirection(myPossibleMove.moveDirection);
    cout << endl;
  }

  myPossibleMove.gameField.removeAt(myPossibleMove.flingNumber);

  switch (myPossibleMove.moveDirection)
  {
  case UP:

    //std::cout << " up" << std::endl;
    for (int i = 0; i < myPossibleMove.gameField.length(); i++)
    {
      if (myPossibleMove.gameField.at(i).y() > y && myPossibleMove.gameField.at(i).x() == x)
      {
        myPossibleMove.gameField[i].setY(myPossibleMove.gameField.at(i).y() - 1);
      }
    }

    break;

  case DOWN:

    //std::cout << " down" << std::endl;
    for (int i = 0; i < myPossibleMove.gameField.length(); i++)
    {
      if (myPossibleMove.gameField.at(i).y() < y && myPossibleMove.gameField.at(i).x() == x)
      {
        myPossibleMove.gameField[i].setY(myPossibleMove.gameField.at(i).y() + 1);
      }
    }

    break;

  case LEFT:

    //std::cout << " left" << std::endl;
    for (int i = 0; i < myPossibleMove.gameField.length(); i++)
    {
      if (myPossibleMove.gameField.at(i).x() < x && myPossibleMove.gameField.at(i).y() == y)
      {
        myPossibleMove.gameField[i].setX(myPossibleMove.gameField.at(i).x() + 1);
      }
    }

    break;

  case RIGHT:

    //std::cout << " right" << std::endl;
    for (int i = 0; i < myPossibleMove.gameField.length(); i++)
    {
      if (myPossibleMove.gameField.at(i).x() > x && myPossibleMove.gameField.at(i).y() == y)
      {
        myPossibleMove.gameField[i].setX(myPossibleMove.gameField.at(i).x() - 1);
      }
    }

    break;
  }

  if (debug)
  {
    cout << "gameField after move: " << endl;
    printFlings(myPossibleMove.gameField);
  }
}

void printPossibleMoves(QList<possibleMove> possibleMoves)
{
  string direction;

  cout << possibleMoves.length() << " possible moves:" << endl;

  for (int i = 0; i < possibleMoves.length(); i++)
  {
    switch (possibleMoves.value(i).moveDirection)
    {
    case UP:
      direction = "up";
      break;

    case DOWN:
      direction = "down";
      break;

    case LEFT:
      direction = "left";
      break;

    case RIGHT:
      direction = "right";
      break;

    default:
      direction = "undefined";
    }

    cout << "possible move fling nr: " << possibleMoves.value(i).flingNumber << " direction: " << direction.c_str() << endl;
  }

  cout << dashedLine.c_str() << endl;
}

int main(int argc, char* argv[])
{
  bool debug = false;

  const int argumentCount = 4;

  if (argc < argumentCount)
  {
    cout << "argument count must be: " << argumentCount << endl;
    cout << "usage: fling.exe file.txt stopAfterFirstSolution printResults" << endl;
    return 0;
  }

  QString fileName = argv[1];

  QList<QPoint> gameField = createGameField(fileName, debug);

  if (debug)
  {
    printFlings(gameField);
  }

  QList<possibleMove> possibleMoves;
  QList<possibleMove> notAllowedPossibleMoves;
  QList<QPair<QPoint, Direction> > history;

  QString stopAfterFirstSolutionString = argv[2];
  bool stopAfterFirstSolution = false;

  if (stopAfterFirstSolutionString == "1")
  {
    stopAfterFirstSolution = true;
  }

  QString printResultsString = argv[3];
  bool printResults = false;

  if (printResultsString == "1")
  {
    printResults = true;
  }

#ifdef Q_WS_WIN
  LARGE_INTEGER frequency;
  QueryPerformanceFrequency(&frequency);
  LARGE_INTEGER start;
  QueryPerformanceCounter(&start);
#endif

  // analyse possible moves
  int solutionCounter = 0;

  do
  {
    notAllowedPossibleMoves.clear();

    for (int i = 0; i < gameField.length() - 1; i++)
    {
      for (int j = i + 1; j < gameField.length(); j++)
      {
        // check if x is the same
        if (gameField.at(i).x() == gameField.at(j).x())
        {
          int distance = abs(gameField.at(i).y() - gameField.at(j).y());
          possibleMove possibleMove1;
          possibleMove possibleMove2;
          possibleMove1.flingNumber = i;
          possibleMove2.flingNumber = j;
          possibleMove1.gameField = gameField;
          possibleMove2.gameField = gameField;
          possibleMove1.history = history;
          possibleMove2.history = history;

          if (gameField.at(i).y() < gameField.at(j).y())
          {
            possibleMove1.moveDirection = UP;
            possibleMove2.moveDirection = DOWN;
          }
          else
          {
            possibleMove1.moveDirection = DOWN;
            possibleMove2.moveDirection = UP;
          }

          if (distance > 1)
          {
            if (!possibleMoves.contains(possibleMove1) && !notAllowedPossibleMoves.contains(possibleMove1))
            {
              possibleMoves.append(possibleMove1);
            }

            if (!possibleMoves.contains(possibleMove2) && !notAllowedPossibleMoves.contains(possibleMove2))
            {
              possibleMoves.append(possibleMove2);
            }
          }
          else
          {
            if (!notAllowedPossibleMoves.contains(possibleMove1))
            {
              notAllowedPossibleMoves.append(possibleMove1);
            }

            if (!notAllowedPossibleMoves.contains(possibleMove2))
            {
              notAllowedPossibleMoves.append(possibleMove2);

            }
          }
        }

        // check if y is the same
        if (gameField.at(i).y() == gameField.at(j).y())
        {
          int distance = abs(gameField.at(i).x() - gameField.at(j).x());

          possibleMove possibleMove1;
          possibleMove possibleMove2;
          possibleMove1.flingNumber = i;
          possibleMove2.flingNumber = j;
          possibleMove1.gameField = gameField;
          possibleMove2.gameField = gameField;
          possibleMove1.history = history;
          possibleMove2.history = history;

          if (gameField.at(i).x() < gameField.at(j).x())
          {
            possibleMove1.moveDirection = RIGHT;
            possibleMove2.moveDirection = LEFT;
          }
          else
          {
            possibleMove1.moveDirection = LEFT;
            possibleMove2.moveDirection = RIGHT;
          }

          if (distance > 1)
          {
            if (!possibleMoves.contains(possibleMove1) && !notAllowedPossibleMoves.contains(possibleMove1))
            {
              possibleMoves.append(possibleMove1);
            }

            if (!possibleMoves.contains(possibleMove2) && !notAllowedPossibleMoves.contains(possibleMove2))
            {
              possibleMoves.append(possibleMove2);
            }
          }
          else
          {
            if (!notAllowedPossibleMoves.contains(possibleMove1))
            {
              notAllowedPossibleMoves.append(possibleMove1);
            }

            if (!notAllowedPossibleMoves.contains(possibleMove2))
            {
              notAllowedPossibleMoves.append(possibleMove2);

            }
          }
        }
      }
    }

    if (debug)
    {
      cout << "possibleMoves: " << endl;
      printPossibleMoves(possibleMoves);
    }

    // do last possible move
    moveFling(possibleMoves.last(), debug);

    if (possibleMoves.last().gameField.length() == 1)
    {
      solutionCounter++;

      if (printResults)
      {
        cout << "found solution nr. " << solutionCounter << endl;

        for (int i = 0; i < possibleMoves.last().history.length(); i++)
        {
          cout << "move fling x: " << possibleMoves.last().history.at(i).first.x();
          cout << " y: " << possibleMoves.last().history.at(i).first.y() << " ";
          printDirection(possibleMoves.last().history.at(i).second);
          cout << endl;
        }

        cout << dashedLine.c_str() << endl;
      }

      if (stopAfterFirstSolution)
      {
        break;
      }
    }

    gameField = possibleMoves.last().gameField;
    history = possibleMoves.last().history;

    // remove played move
    possibleMoves.removeLast();
  }
  while (possibleMoves.length() > 0 || solutionCounter == 0); // hier kann es zur Endlosschleife kommmen, wenn es keine Lösung gibt

#ifdef Q_WS_WIN
  LARGE_INTEGER end;
  QueryPerformanceCounter(&end);
  double duration = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
  printf(" Duration: %4.4f sec.\n", duration);
#endif

  cout << "solution count: " << solutionCounter << endl;

  return 0;
}
