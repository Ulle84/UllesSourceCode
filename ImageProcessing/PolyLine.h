#ifndef POLYLINE_H
#define POLYLINE_H

#include <list>

#include "Point.h"
#include "RunLengthCode.h"

class Rectangle;

class PolyLine
{
public:
  PolyLine();

  void setPoints(const std::list<Point>& points);
  void appendPoint(const Point& point);

  Rectangle getBoundingRectangle();

  RunLengthCode toRunLengthCode();

  std::list<Point> m_points; // TODO really public?

private:
  void updateMinMavValues();

  unsigned int m_xMin;
  unsigned int m_xMax;
  unsigned int m_yMin;
  unsigned int m_yMax;

};

#endif // POLYLINE_H
