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


void PolyLine::updateMinMavValues()
{
  m_xMin = std::numeric_limits<unsigned int>::max();
  m_xMax = std::numeric_limits<unsigned int>::min();
  m_yMin = std::numeric_limits<unsigned int>::max();
  m_yMax = std::numeric_limits<unsigned int>::min();

  for (auto it = m_points.begin(); it != m_points.end(); it++)
  {
    if (it->m_x < m_xMin)
    {
      m_xMin = it->m_x;
    }
    else if (it->m_x > m_xMax)
    {
      m_xMax = it->m_x;
    }

    if (it->m_y < m_yMin)
    {
      m_yMin = it->m_y;
    }
    else if (it->m_y > m_yMax)
    {
      m_yMax = it->m_y;
    }
  }
}

Rectangle PolyLine::getBoundingRectangle()
{
  if (m_points.empty())
  {
    // TODO throw exception?
  }

  updateMinMavValues();

  return Rectangle(Point(m_xMin, m_yMin), m_xMax - m_xMin + 1, m_yMax - m_yMin + 1);
}

RunLengthCode PolyLine::toRunLengthCode()
{
  updateMinMavValues();

  PolyLine converted = *this;

  for (auto it = converted.m_points.begin(); it != converted.m_points.end(); it++)
  {
     it->m_x -= m_xMin;
     it->m_y -= m_yMin;
  }

  Rectangle rectangle = getBoundingRectangle();

  StructuringElement structuringElement(rectangle.m_width, rectangle.m_height, false);
  structuringElement.setPolyLine(true, converted);
  structuringElement.fillBackground(false, true);
  structuringElement.invert();
  structuringElement.setPolyLine(true, converted);

  RunLengthCode runLengthCode = structuringElement.getRunLengthCode(true);

  for (auto it = runLengthCode.begin(); it != runLengthCode.end(); it++)
  {
    it->m_startPoint.m_x += m_xMin;
    it->m_startPoint.m_y += m_yMin;
  }

  return runLengthCode;
}

