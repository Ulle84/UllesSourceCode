#ifndef POINT_H
#define POINT_H

#include <list>

class Point
{
public:
  Point();
  Point(float x, float y);

  float m_x;
  float m_y;
};

typedef std::list<Point> Points;

#endif // POINT_H
