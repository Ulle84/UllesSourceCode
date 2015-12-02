#ifndef POLYLINE_H
#define POLYLINE_H

#include <list>

#include "Point.h"

class PolyLine
{
public:
  PolyLine();

  void setPoints(const std::list<Point>& points);

  std::list<Point> m_points; // TODO really public?
};

#endif // POLYLINE_H
