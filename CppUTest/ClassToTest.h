#pragma once

class ClassToTest
{
public:
  ClassToTest();
  ClassToTest(const ClassToTest &rhs);

  ~ClassToTest();

  ClassToTest& operator= (const ClassToTest &rhs);

  int getValue() const;
  void setValue(int value);

  void incrementValue();
  void addValue(int valueToAdd);

  bool equalsValue(int value);

  unsigned char* getBuffer() const;

private:
  int m_value;
  unsigned char* m_buffer;
  unsigned int m_bufferLength;

  friend class TEST_ClassTest_Assignment_Test;
  friend class TEST_ClassTest_CopyConstructor_Test;
};

