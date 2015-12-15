#ifndef POLYLINE_H
#define POLYLINE_H

#include <list>

#include "Rectangle.h"
#include "Point.h"
#include "RunLengthCode.h"

// TODO typedef std::list<Point> PolyLine?

class PolyLine
{
public:
  PolyLine();

  void setPoints(const std::list<Point>& points);
  void appendPoint(const Point& point);

  Rectangle getBoundingRectangle();

  RunLengthCode toRunLengthCode();

  std::list<Point> m_points; // TODO really public?
};

#endif // POLYLINE_H
