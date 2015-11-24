#include <iostream>

#include "FilterMask.h"

FilterMask::FilterMask(unsigned int width, unsigned int height) :
  m_width(width),
  m_height(height)
{
  m_buffer = new int[m_width * m_height];
  m_matrix = new int*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_buffer[i * m_width];
  }

  memset(m_buffer, 0, m_width * m_height);
}

FilterMask::~FilterMask()
{

}

void FilterMask::setReferencePoint(const Point &referencePoint)
{
  m_referencePoint = referencePoint;
}

FilterMask::FilterMask()
{

}

