#include "Class.h"

Class::Class(const QString& name) :
  m_name(name)
{

}

QString Class::name() const
{
  return m_name;
}

void Class::setName(const QString& name)
{
  m_name = name;
}

QStringList Class::baseClasses() const
{
  return m_baseClasses;
}

void Class::setBaseClasses(const QStringList& baseClasses)
{
  m_baseClasses = baseClasses;
}

QString Class::header() const
{
  return m_header;
}

void Class::setHeader(const QString& header)
{
  m_header = header;
}

