#ifndef STRUCTURINGELEMENTGENERATOR_H
#define STRUCTURINGELEMENTGENERATOR_H

#include "Matrix.h"

class StructuringElementGenerator
{
public:
  StructuringElementGenerator();

  static StructuringElement neighborhood4();
  static StructuringElement neighborhood8();
};

#endif // STRUCTURINGELEMENTGENERATOR_H
