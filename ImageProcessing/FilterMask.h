#ifndef FILTERMASK_H
#define FILTERMASK_H

#include "Point.h"

class FilterMask
{
public:
  FilterMask(unsigned int width, unsigned int height);
  ~FilterMask();

  void setReferencePoint(const Point& referencePoint);

private:
  unsigned int m_width;
  unsigned int m_height;

  Point m_referencePoint;

  int* m_buffer;
  int** m_matrix; // TODO how to set up the matrix from the outside

  FilterMask();
};

#endif // FILTERMASK_H
