#include "RandomNumberGenerator.h"

#include <stdlib.h>
#include <time.h>

RandomNumberGenerator::RandomNumberGenerator()
{
  // do not use!
}

RandomNumberGenerator::RandomNumberGenerator(int minimum, int maximum)
{
  srand(time(NULL));
  randomNumber = 0;
  previousRandomNumber = 0;
  this->minimum = minimum;
  this->maximum = maximum;
  this->difference = maximum - minimum + 1;
}

int RandomNumberGenerator::getRandomNumber()
{
  previousRandomNumber = randomNumber;
  bool numbersAreEqual = true;

  while (numbersAreEqual)
  {
    randomNumber = (rand() % difference) + minimum;

    if (previousRandomNumber != randomNumber)
    {
      numbersAreEqual = false;
    }
  }

  return randomNumber;
}

int RandomNumberGenerator::getSumOfLastTwoRandomNumbers()
{
  return previousRandomNumber + randomNumber;
}


