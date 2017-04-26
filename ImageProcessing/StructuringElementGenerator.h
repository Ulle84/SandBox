#ifndef STRUCTURINGELEMENTGENERATOR_H
#define STRUCTURINGELEMENTGENERATOR_H

#include "Matrix.h"

// TODO hold references of generated StructuringElement -> implement singleton which holds the references and deletes them in destructor

class StructuringElementGenerator
{
public:
  StructuringElementGenerator();

  static StructuringElement neighborhood4();
  static StructuringElement neighborhood8();
  static StructuringElement circle(unsigned int radius = 2);
  static StructuringElement polyLineFillTest(unsigned int type, bool fill);
};

#endif // STRUCTURINGELEMENTGENERATOR_H
