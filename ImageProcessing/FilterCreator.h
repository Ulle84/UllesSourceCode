#ifndef FILTERCREATOR_H
#define FILTERCREATOR_H

#include "Matrix.h"

class FilterCreator
{
public:
  FilterCreator();

  static Filter mean(unsigned int width, unsigned int height = 0);
  static Filter binomial(unsigned int width, unsigned int height = 0);
  static Filter laplacian();
  static Filter laplacianBig();
  static Filter laplacian2();
  static Filter sobelHorizontal();
  static Filter sobelVertical();
};

#endif // FILTERCREATOR_H
