#ifndef POINT_H
#define POINT_H

#include <list>

class Point
{
public:
  Point();
  Point(unsigned int x, unsigned int y);

  unsigned int m_x; // TODO float?
  unsigned int m_y;
};

typedef std::list<Point> Points;

#endif // POINT_H
