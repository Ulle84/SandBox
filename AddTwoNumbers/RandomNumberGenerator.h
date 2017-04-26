#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

class RandomNumberGenerator
{
public:
  RandomNumberGenerator(int minimum, int maximum);
  int getRandomNumber();
  int getSumOfLastTwoRandomNumbers();

private:
  RandomNumberGenerator();
  int randomNumber;
  int previousRandomNumber;
  int minimum;
  int maximum;
  int difference;
};

#endif // RANDOMNUMBERGENERATOR_H
