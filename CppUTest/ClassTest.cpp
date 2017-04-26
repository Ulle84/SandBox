#include <string>

#include "CPPUTest\CppUTest\TestHarness.h"
#include "ClassToTest.h"

TEST_GROUP(ClassTest)
{
  void setup()
  {

  }

  void teardown()
  {

  }
};

TEST(ClassTest, InitValueWithZero)
{
  ClassToTest classToTest;

  CHECK(classToTest.getValue() == 0);
  CHECK(classToTest.equalsValue(0));
}

TEST(ClassTest, SetAndGet)
{
  ClassToTest classToTest;
  classToTest.setValue(10);

  CHECK(classToTest.equalsValue(10));
  CHECK(classToTest.getValue() == 10);
}

TEST(ClassTest, Equals)
{
  ClassToTest classToTest;
  classToTest.setValue(10);

  CHECK(classToTest.equalsValue(10));
}

TEST(ClassTest, Assignment)
{
  ClassToTest classToTest1;
  ClassToTest classToTest2;

  classToTest1.setValue(10);

  classToTest2 = classToTest1;

  CHECK(classToTest2.equalsValue(10));
  CHECK(classToTest1.m_bufferLength == classToTest2.m_bufferLength);

  CHECK(memcmp(classToTest1.m_buffer, classToTest2.m_buffer, classToTest1.m_bufferLength) == 0);
}

TEST(ClassTest, CopyConstructor)
{
  ClassToTest classToTest1;
  classToTest1.setValue(10);

  ClassToTest classToTest2(classToTest1);

  CHECK(classToTest2.equalsValue(10));
  CHECK(classToTest1.m_bufferLength == classToTest2.m_bufferLength);

  CHECK(memcmp(classToTest1.m_buffer, classToTest2.m_buffer, classToTest1.m_bufferLength) == 0);
}