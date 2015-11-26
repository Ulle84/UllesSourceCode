#include <iostream>

#include "LookUpTable.h"

LookUpTable::LookUpTable() :
  m_size(256)
{
  m_values = new unsigned char[m_size];
  clear();
}

LookUpTable::LookUpTable(const LookUpTable &rhs)
{
  m_size = rhs.m_size;

  m_values = new unsigned char[m_size];
  memcpy(m_values, rhs.m_values, m_size);
}

LookUpTable::~LookUpTable()
{
  delete[] m_values;
}

LookUpTable &LookUpTable::operator=(const LookUpTable &rhs)
{
  if (&rhs != this)
  {
    m_size = rhs.m_size;

    delete[] m_values;
    m_values = new unsigned char[m_size];
    memcpy(m_values, rhs.m_values, m_size);
  }

  return *this;
}

void LookUpTable::clear()
{
  memset(m_values, 0, m_size);
}

