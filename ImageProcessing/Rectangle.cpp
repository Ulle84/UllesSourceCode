#include "MathHelper.h"
#include "Rectangle.h"

Rectangle::Rectangle() :
  m_width(0),
  m_height(0)
{

}

Rectangle::Rectangle(const Point &origin, unsigned int width, unsigned int height, float angle) :
  m_origin(origin),
  m_width(width),
  m_height(height),
  m_angle(angle)
{

}

Points Rectangle::getEdgePoints() const
{
  Points edgePoints;

  edgePoints.push_back(m_origin);
  edgePoints.push_back(MathHelper::calcEndPoint(m_origin, m_angle + 90, m_height)); // pointing in y direction
  edgePoints.push_back(MathHelper::calcEndPoint(edgePoints.back(), m_angle, m_width)); // pointing in x and y direction
  edgePoints.push_back(MathHelper::calcEndPoint(m_origin, m_angle, m_width)); // pointing in x direction

  return edgePoints;
}

PolyLine Rectangle::toPolyLine() const
{
  PolyLine polyLine;

  Points points = getEdgePoints();
  points.push_back(m_origin);

  polyLine.setPoints(points);

  return polyLine;
}

float Rectangle::x()
{
  return m_origin.x();
}

void Rectangle::setX(float x)
{
  m_origin.setX(x);
}

float Rectangle::y()
{
  return m_origin.y();
}

void Rectangle::setY(float y)
{
  m_origin.setY(y);
}

float Rectangle::width()
{
  return m_width;
}

void Rectangle::setWidth(float width)
{
  m_width = width;
}

float Rectangle::height()
{
  return m_height;
}

void Rectangle::setHeight(float height)
{
  m_height = height;
}


