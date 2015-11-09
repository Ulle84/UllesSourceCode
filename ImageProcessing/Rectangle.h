#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"

class Rectangle
{
public:
  Rectangle();
  Rectangle(const Point& topLeftCorner, unsigned int width, unsigned int height);

  Point m_topLeftCorner;
  unsigned int m_width;
  unsigned int m_height;
};

#endif // RECTANGLE_H
