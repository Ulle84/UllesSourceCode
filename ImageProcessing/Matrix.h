#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <typeinfo>
#include <string>

// TODO rename depth to qtyLayers

template<typename T>
class Matrix
{
public:
  Matrix();
  Matrix(unsigned int width, unsigned int height, unsigned int qtyLayers = 1);
  Matrix(const Matrix& rhs);
  Matrix(Matrix&& rhs);
  virtual ~Matrix();

  Matrix& operator= (const Matrix& rhs);
  Matrix& operator= (Matrix&& rhs);

  unsigned int getWidth();
  unsigned int getHeight();
  unsigned int getDepth();

  void printValues();
  void setIncreasingValues();
  void clear();
  void setAllValues(T value);
  //unsigned char getBits
  
protected:
  T*** m_values;
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_qtyLayers;

private:
  T** m_lines;
  void create();
  void destroy();
};

template<typename T>
Matrix<T>::Matrix() :
  m_width(512),
  m_height(512),
  m_qtyLayers(1)
{
  std::cout << "default constructor of matrix" << std::endl;
  create();
  clear();
}

template<typename T>
Matrix<T>::Matrix(const Matrix &rhs)
{
  std::cout << "copy constructor of matrix" << std::endl;
  m_width = rhs.m_width;
  m_height = rhs.m_height;
  m_qtyLayers = rhs.m_qtyLayers;

  create();

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    memcpy(m_values[z][0], rhs.m_values[z][0], m_width * m_height * sizeof(T));
  }
}

template<typename T>
Matrix<T>::Matrix(Matrix&& rhs)
{
  std::cout << "move constructor of matrix" << std::endl;
  // TODO
  /*
m_height = rhs.m_height;
  m_width = rhs.m_width;
  m_pixels = rhs.m_pixels;
  m_matrix = rhs.m_matrix;

  rhs.m_height = 0;
  rhs.m_width = 0;
  rhs.m_pixels = nullptr;
  rhs.m_matrix = nullptr;
  */
}

template<typename T>
Matrix<T>::Matrix(unsigned int width, unsigned int height, unsigned int qtyLayers) :
  m_width(width),
  m_height(height),
  m_qtyLayers(qtyLayers)
{
  std::cout << "value constructor of matrix" << std::endl;

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

  create();
  clear();
}

template<typename T>
void Matrix<T>::create()
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
  }
}

template<typename T>
void Matrix<T>::destroy()
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
Matrix<T>::~Matrix()
{
  std::cout << "destructor of matrix" << std::endl;
  destroy();
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& rhs)
{
  std::cout << "asignment operator of matrix" << std::endl;
  if (&rhs != this)
  {
    if (m_width != rhs.m_width || m_height != rhs.m_height || m_qtyLayers != rhs.m_qtyLayers)
    {
      // TODO improve performance -> rearange buffer if sizes match
      destroy();

      m_width = rhs.m_width;
      m_height = rhs.m_height;
      m_qtyLayers = rhs.m_qtyLayers;

      create();
    }

    for (unsigned int z = 0; z < m_qtyLayers; z++)
    {
      memcpy(m_values[z][0], rhs.m_values[z][0], m_width * m_height * sizeof(T));
    }
  }

  return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& rhs)
{
  std::cout << "move asignment operator of matrix" << std::endl;

  /*
   * if (&rhs != this)
  {
    delete[] m_pixels;
    delete[] m_matrix;

    m_height = rhs.m_height;
    m_width =  rhs.m_width;
    m_pixels = rhs.m_pixels;
    m_matrix = rhs.m_matrix;

    rhs.m_height = 0;
    rhs.m_width = 0;
    rhs.m_pixels = nullptr;
    rhs.m_matrix = nullptr;
  }
  return *this;*/

}

template<typename T>
void Matrix<T>::clear()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    memset(m_lines[z], 0, m_width * m_height * sizeof(T));
  }
}

template<typename T>
void Matrix<T>::setAllValues(T value)
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        m_values[z][y][x] = value;
      }
    }
  }
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
        if (sizeof(T) > 1)
        {
          std::cout << m_values[z][y][x] << " ";
        }
        else
        {
          std::cout << (int) m_values[z][y][x] << " ";
        }

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
