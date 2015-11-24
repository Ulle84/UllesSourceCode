#ifndef FILTERMASK_H
#define FILTERMASK_H

#include "Point.h"

class FilterMask
{
public:
  FilterMask(unsigned int width, unsigned int height);
  ~FilterMask();

  void setReferencePoint(const Point& referencePoint);
  int getSumOfMatrix() const;

  int** m_matrix; // TODO how to set up the matrix from the outside

  unsigned int m_width; // TODO declare private
  unsigned int m_height; // TODO declare private

private:


  Point m_referencePoint;

  int* m_buffer;


  FilterMask();

  friend class Image; // TODO is this neccessary?
};

#endif // FILTERMASK_H
