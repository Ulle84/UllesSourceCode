#include <iostream>
#include <limits>

#include <QDebug>

#include "Histogram.h"

Histogram::Histogram() :
  m_size(256)
{
  m_values = new unsigned int[m_size];
  clear();
}

Histogram::Histogram(const Histogram &rhs)
{
  m_size = rhs.m_size;

  m_values = new unsigned int[m_size];
  memcpy(m_values, rhs.m_values, m_size * sizeof(unsigned int));
}

Histogram::~Histogram()
{
  delete[] m_values;
}

Histogram &Histogram::operator=(const Histogram &rhs)
{
  if (&rhs != this)
  {
    m_size = rhs.m_size;

    delete[] m_values;
    m_values = new unsigned int[m_size];
    memcpy(m_values, rhs.m_values, m_size * sizeof(unsigned int));
  }

  return *this;
}

void Histogram::print(unsigned int threshold)
{
  qDebug() << "histogram - threshold:" << threshold;
  for (unsigned int i = 0; i < m_size; i++)
  {
    if (m_values[i] >= threshold)
    {
      qDebug() << i << m_values[i];
    }
  }
}

void Histogram::clear()
{
  memset(m_values, 0, m_size * sizeof(unsigned int));
}

unsigned int Histogram::getMaxValue() const
{
  unsigned int maximum =  std::numeric_limits<unsigned int>::min();

  for (unsigned int i = 0; i < m_size; i++)
  {
    if (m_values[i] > maximum)
    {
      maximum = m_values[i];
    }
  }

  return maximum;
}

