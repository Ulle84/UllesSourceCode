#include <limits>

#include "PolyLine.h"
#include "Matrix.h"

PolyLine::PolyLine()
{

}

void PolyLine::setPoints(const std::list<Point> &points)
{
  m_points = points;
}

void PolyLine::appendPoint(const Point &point)
{
  m_points.push_back(point);
}

Rectangle PolyLine::getBoundingRectangle()
{
  if (m_points.empty())
  {
    // TODO throw exception?
  }

  unsigned int xMin = std::numeric_limits<unsigned int>::max();
  unsigned int xMax = std::numeric_limits<unsigned int>::min();
  unsigned int yMin = std::numeric_limits<unsigned int>::max();
  unsigned int yMax = std::numeric_limits<unsigned int>::min();

  for (auto it = m_points.begin(); it != m_points.end(); it++)
  {
    if (it->m_x < xMin)
    {
      xMin = it->m_x;
    }
    else if (it->m_x > xMax)
    {
      xMax = it->m_x;
    }

    if (it->m_y < yMin)
    {
      yMin = it->m_y;
    }
    else if (it->m_y > yMax)
    {
      yMax = it->m_y;
    }
  }

  return Rectangle(Point(xMin, yMin), xMax - xMin + 1, yMax - yMin + 1);
}

RunLengthCode PolyLine::toRunLengthCode()
{
  // TODO furhter implemenation after testing the Matrix::fill function

  /*Rectangle rectangle = getBoundingRectangle();

  StructuringElement structuringElement(rectangle.m_width, rectangle.m_height, false);*/

  // TODO use correct dimensions see uncommented code above

  /*StructuringElement structuringElement(12, 12, false);

  structuringElement.setPolyLine(true, *this);

  structuringElement.printValuesToConsole("structuring element");*/


  RunLengthCode runLengthCode;



  return runLengthCode;
}

