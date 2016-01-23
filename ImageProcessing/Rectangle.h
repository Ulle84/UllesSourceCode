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

  float x();
  void setX(float x);

  float y();
  void setY(float y);

  float width();
  void setWidth(float width);

  float height();
  void setHeight(float height);

  //void setBottomRight

  Point m_origin; // TODO -> private
  unsigned int m_width;
  unsigned int m_height;
  float m_angle;
};

#endif // RECTANGLE_H
