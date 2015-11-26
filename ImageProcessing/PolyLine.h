#ifndef POLYLINE_H
#define POLYLINE_H

#include <QList>

#include "Point.h"

class PolyLine
{
public:
  PolyLine();

  void setPoints(const QList<Point>& points);

private:
  QList<Point> m_points;

  friend class Image;
};

#endif // POLYLINE_H
