#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <list>

#include "Point.h"
#include "PolyLine.h"

class Rectangle
{
public:
  Rectangle();
  Rectangle(const Point& origin, unsigned int width, unsigned int height, float angle = 0.0);
  //Rectangle(const Line& line, unsigned int height); // TODO

  Points getEdgePoints() const;
  PolyLine toPolyLine() const;

  Point m_origin;
  unsigned int m_width;
  unsigned int m_height;
  float m_angle;
};

#endif // RECTANGLE_H
