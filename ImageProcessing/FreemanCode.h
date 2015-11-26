#ifndef FREEMANCODE_H
#define FREEMANCODE_H

#include <QList>

#include "Point.h"

class FreemanCode
{
public:
  FreemanCode();

  void setStartPoint(const Point& startPoint);
  void setDirections(const QList<unsigned char>& directions);

private:
  Point m_startPoint;
  QList<unsigned char> m_directions;

  friend class Image;
};

#endif // FREEMANCODE_H
