#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include "Phase.h"

class Action
{
public:
  enum Type
  {
    Undefined = 0,
    Fold,
    Check,
    Call,
    Bet,
    Raise,
    CheckRaise,
    ReRaise
  };

  // todo move to private?
  Phase m_phase;
  QString m_player;
  Type m_type;
  double m_value;

  Action(Phase phase, const QString& player, Type type, double value);

  QString toString();

private:

};

#endif // ACTION_H
