#ifndef POLYLINE_H
#define POLYLINE_H

#include <list>

#include "Point.h"

class PolyLine
{
public:
  PolyLine();

  void setPoints(const std::list<Point>& points);

private:
  std::list<Point> m_points;

  friend class Image;
};

#endif // POLYLINE_H
