#include <string.h>
#include <cstdlib>

#include "ClassToTest.h"

ClassToTest::ClassToTest() :
  m_value(0),
  m_bufferLength(10)
{
  m_buffer = new unsigned char [m_bufferLength];

  unsigned char* t = m_buffer;

  for (unsigned int i = 0; i < m_bufferLength; i++)
  {
    *t++ = rand();
  }
}

ClassToTest::ClassToTest( const ClassToTest &rhs )
{
  m_value = rhs.m_value;
  m_bufferLength = rhs.m_bufferLength;

  m_buffer = new unsigned char [m_bufferLength];
  memcpy(m_buffer, rhs.m_buffer, m_bufferLength);
}

ClassToTest& ClassToTest::operator=( const ClassToTest &rhs )
{
  if (&rhs != this)
  {
    m_value = rhs.m_value;

    if (m_bufferLength != rhs.m_bufferLength)
    {
      m_bufferLength = rhs.m_bufferLength;

      delete[] m_buffer;
      m_buffer = new unsigned char [m_bufferLength];
    }    

    memcpy(m_buffer, rhs.m_buffer, m_bufferLength);
  }

  return *this;
}


ClassToTest::~ClassToTest()
{
  delete[] m_buffer;
}

int ClassToTest::getValue() const
{
  return m_value;
}

void ClassToTest::incrementValue()
{
  m_value++;
}

void ClassToTest::setValue(int value)
{
  m_value = value;
}

void ClassToTest::addValue(int valueToAdd)
{
  m_value += valueToAdd;
}

bool ClassToTest::equalsValue(int value)
{
  return m_value == value;
}

unsigned char* ClassToTest::getBuffer() const
{
  return m_buffer;
}


