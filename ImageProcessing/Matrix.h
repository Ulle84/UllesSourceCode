#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template<typename T>
class Matrix
{
public:
  Matrix();
  Matrix(unsigned int width, unsigned int height, unsigned int depth);
  virtual ~Matrix();

  unsigned int getWidth();
  unsigned int getHeight();
  unsigned int getDepth();

  void test();
  
protected:
  T*** m_values;
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_depth;

private:
  T** m_buffers;
  T*** m_lines;
  void init();
};

template<typename T>
Matrix<T>::Matrix() :
  m_width(512),
  m_height(512),
  m_depth(1)
{
  init();
}

template<typename T>
Matrix<T>::Matrix(unsigned int width, unsigned int height, unsigned int depth) :
  m_width(width),
  m_height(height),
  m_depth(depth)
{
  init();
}

template<typename T>
void Matrix<T>::init()
{
  m_values = new T**[m_depth];
  m_lines = new T**[m_depth];
  m_buffers = new T*[m_depth];

  for (unsigned int d = 0; d < m_depth; d++)
  {
    m_buffers[d] = new T[m_width * m_height];
    m_lines[d] = new T*[m_height];

    for (unsigned int i = 0; i < m_height; i++)
    {
      m_lines[d][i] = &m_buffers[d][i * m_width];
    }

    memset(m_buffers[d], 0, m_width * m_height);

    //m_values[d] = m_lines[d][0];
  }

  // allocate memory line by line
  /*m_values = new T**[m_depth];

  for (unsigned int d = 0; d < m_depth; d++)
  {
    m_values[d] = new T*[m_height];
    for (unsigned int i = 0; i < m_height; i++)
    {
      m_values[d][i] = new T[m_width];
    }
  }*/
}

template<typename T>
Matrix<T>::~Matrix()
{
  /*for (unsigned int d = 0; d < m_depth; d++)
  {
    for (unsigned int i = 0; i < m_height; i++)
    {
      delete[] m_values[d][i];
    }
    delete[] m_values[d];
  }
  delete[] m_values;*/
}

template<typename T>
unsigned int Matrix<T>::getWidth()
{
  return m_width;
}

template<typename T>
unsigned int Matrix<T>::getHeight()
{
  return m_height;
}

template<typename T>
unsigned int Matrix<T>::getDepth()
{
  return m_depth;
}

template<typename T>
void Matrix<T>::test()
{
  //[layer][line][colum]
  //m_values[0][0][0] = 255;
}

#endif // MATRIX_H
