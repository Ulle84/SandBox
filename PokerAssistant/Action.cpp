#include "Action.h"

Action::Action(Phase phase, const QString &player, Type type, double value) :
  m_phase(phase),
  m_player(player),
  m_type(type),
  m_value(value)
{

}

QString Action::toString()
{
  QString info;

  switch(m_phase)
  {
  case PreFlop:
    info.append("PreFlop");
    break;

  case Flop:
    info.append("Flop");
    break;

  case Turn:
    info.append("Turn");
    break;

  case River:
    info.append("River");
    break;

  }

  info.append(": ");
  info.append(m_player);
  info.append(" ");

  switch(m_type)
  {
  case Fold:
    info.append("folds");
    break;

  case Check:
    info.append("checks");
    break;

  case Call:
    info.append("calls");
    break;

  case Bet:
    info.append(QString("bets %1").arg(m_value));
    break;

  case Raise:
  case CheckRaise:
  case ReRaise:
    info.append(QString("raises %1").arg(m_value));
    break;
  }


  info.append("\n");

  return info;
}
