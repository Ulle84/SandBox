#ifndef GUESS_H
#define GUESS_H

#include <QList>

class Guess
{
public:
    Guess();
    QList<int> m_numbers;
    int bulls; // matching digits, which are in their right positions
    int cows; // matching digits
};

#endif // GUESS_H
