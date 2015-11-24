#include <iostream>

#include "FilterMask.h"

FilterMask::FilterMask(unsigned int width, unsigned int height) :
  m_width(width),
  m_height(height)
{
  m_referencePoint.m_x = m_width / 2;
  m_referencePoint.m_y = m_height / 2;

  m_buffer = new int[m_width * m_height];
  m_matrix = new int*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_buffer[i * m_width];
  }

  memset(m_buffer, 0, m_width * m_height * sizeof(int));
}

FilterMask::~FilterMask()
{

}

void FilterMask::setReferencePoint(const Point &referencePoint)
{
  m_referencePoint = referencePoint;
}

int FilterMask::getSumOfMatrix() const
{
  int sum = 0;

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      sum += m_matrix[y][x];
    }
  }

  return sum;
}

FilterMask::FilterMask()
{

}
