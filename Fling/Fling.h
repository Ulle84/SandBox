#ifndef FLING_H
#define FLING_H

class Fling
{
public:
  Fling();
  Fling(unsigned int x, unsigned int y);
  unsigned int x;
  unsigned int y;
  void print();
  void setX(unsigned int x);
  void setY(unsigned int y);
};

#endif // FLING_H
