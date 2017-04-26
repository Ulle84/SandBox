#include "Namespace.h"

Namespace::Namespace()
{

}

Namespace::~Namespace()
{

}

int Namespace::startPosition() const
{
  return m_startPosition;
}

int Namespace::stopPosition() const
{
  return m_stopPosition;
}

QString Namespace::name() const
{
  return m_name;
}

void Namespace::setStartPosition(int startPosition)
{
  m_startPosition = startPosition;
}

void Namespace::setStopPosition(int stopPosition)
{
  m_stopPosition = stopPosition;
}

void Namespace::setName(const QString& name)
{
  m_name = name;
}
