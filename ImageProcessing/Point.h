#ifndef POINT_H
#define POINT_H

#include <list>

class Point
{
public:
  Point();
  Point(float x, float y);

  float x();
  void setX(float x);

  float y();
  void setY(float y);

  float m_x; // TODO private
  float m_y;
};

typedef std::list<Point> Points;

#endif // POINT_H
