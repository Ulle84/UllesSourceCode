#ifndef FREEMANCODE_H
#define FREEMANCODE_H

#include <list>

#include "Point.h"

class FreemanCode
{
public:
  FreemanCode();

  void setStartPoint(const Point& startPoint);
  void setDirections(const std::list<unsigned char>& directions);

private:
  Point m_startPoint;
  std::list<unsigned char> m_directions;

  friend class Image;
};

#endif // FREEMANCODE_H
