#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

// TODO rename depth to qtyLayers

template<typename T>
class Matrix
{
public:
  Matrix();
  Matrix(unsigned int width, unsigned int height, unsigned int qtyLayers = 1);
  virtual ~Matrix();

  unsigned int getWidth();
  unsigned int getHeight();
  unsigned int getDepth();

  void printValues();
  void setIncreasingValues();
  
protected:
  T*** m_values;
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_qtyLayers;

private:
  T** m_lines;
  void init();
};

template<typename T>
Matrix<T>::Matrix() :
  m_width(512),
  m_height(512),
  m_qtyLayers(1)
{
  init();
}

template<typename T>
Matrix<T>::Matrix(unsigned int width, unsigned int height, unsigned int qtyLayers) :
  m_width(width),
  m_height(height),
  m_qtyLayers(qtyLayers)
{
  if (m_width == 0)
  {
    m_width = 1;
  }

  if (m_height == 0)
  {
    m_height = 1;
  }

  if (m_qtyLayers == 0)
  {
    m_qtyLayers = 1;
  }

  init();
}

template<typename T>
void Matrix<T>::init()
{
  m_lines = new T*[m_qtyLayers];
  m_values = new T**[m_qtyLayers];

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    m_lines[z] = new T[m_width * m_height];
    m_values[z] = new T*[m_height];

    for (unsigned int y = 0; y < m_height; y++)
    {
      m_values[z][y] = &m_lines[z][y * m_width];
    }

    memset(m_lines[z], 0, m_width * m_height * sizeof(T));
  }
}

template<typename T>
Matrix<T>::~Matrix()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    delete[] m_values[z];
    delete[] m_lines[z];
  }

  delete[] m_values;
  delete[] m_lines;
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
  return m_qtyLayers;
}

template<typename T>
void Matrix<T>::printValues()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    std::cout << "layer " << z << std::endl;

    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        if (m_values[z][y][x] < 10)
        {
          std::cout << " ";
        }

        if (m_values[z][y][x] < 100)
        {
          std::cout << " ";
        }

        std::cout << (int) m_values[z][y][x] << " ";
      }

      std::cout << std::endl;
    }
  }
}

template<typename T>
void Matrix<T>::setIncreasingValues()
{
  T value = 0;
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        m_values[z][y][x] = value++;
      }
    }
  }
}

#endif // MATRIX_H
