#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <Fling.h>
#include <QList>
#include <QString>

class PlayingField
{
public:
  PlayingField();
  PlayingField(QString fileName);
  QList<Fling>* flings;
};

#endif // PLAYINGFIELD_H
