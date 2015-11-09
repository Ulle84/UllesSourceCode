#include "Rectangle.h"

Rectangle::Rectangle() :
  m_width(0),
  m_height(0)
{

}

Rectangle::Rectangle(const Point &topLeftCorner, unsigned int width, unsigned int height) :
  m_topLeftCorner(topLeftCorner),
  m_width(width),
  m_height(height)
{

}

