#include <QCoreApplication>
#include <iostream>

int main(int argc, char* argv[])
{
  unsigned long long number = 4294967297;
  unsigned long long twoPow32 = 4294967296;

  unsigned long highPartOfNumber = number >> 32;
  unsigned long lowPartOfNumber = number;
  unsigned long long lowAndHighPartOfNumber = highPartOfNumber * twoPow32 + lowPartOfNumber;

  std::cout << "number: " << number << std::endl;
  std::cout << "twoPow32: " << twoPow32 << std::endl;
  std::cout << "highPartOfNumber: " << highPartOfNumber << std::endl;
  std::cout << "lowPartOfNumber: " << lowPartOfNumber << std::endl;
  std::cout << "lowAndHighPartOfNumber: " << lowAndHighPartOfNumber << std::endl;

  std::cout << "Press Enter to Exit" << std::endl;
  std::cin.get();
}
