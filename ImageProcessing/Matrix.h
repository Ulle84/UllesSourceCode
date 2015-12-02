#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <typeinfo>
#include <string>
#include <limits>

#include <math.h>

// TODO move all type-independent functionality from Image to Matrix
// TODO use const whereever possible
// TODO sort public functions

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

  unsigned int getWidth() const;
  unsigned int getHeight() const;
  unsigned int getDepth() const;
  T getMinimum() const;
  T getMaximum() const;

  void printValuesToConsole(const std::string& description) const;
  void setIncreasingValues();
  void clear();
  void setAllValues(T value);
  void setValue(T value, unsigned int x, unsigned int y, unsigned int z = 0);

  T getValue(unsigned int x, unsigned int y, unsigned int z = 0) const;
  T* getLayer(unsigned int z) const; // TODO define return value const, so the matrix values can not be changed!

  void setRandomValues();
  void binarize(T threshold);
  void spread();
  
protected:
  T*** m_values;
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_qtyLayers;

private:
  T** m_lines;
  void create();
  void destroy();
  void move(Matrix&& rhs);
  void copy(const Matrix&);
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
  std::cout << "Matrix: copy constructor" << std::endl;
  m_width = rhs.m_width;
  m_height = rhs.m_height;
  m_qtyLayers = rhs.m_qtyLayers;

  create();
  copy(rhs);
}

template<typename T>
Matrix<T>::Matrix(Matrix&& rhs)
{
  std::cout << "Matrix: move constructor" << std::endl;

  move(rhs);
}

template<typename T>
Matrix<T>::Matrix(unsigned int width, unsigned int height, unsigned int qtyLayers) :
  m_width(width),
  m_height(height),
  m_qtyLayers(qtyLayers)
{
  std::cout << "Matrix: value constructor" << std::endl;

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
  std::cout << "Matrix: destructor" << std::endl;
  destroy();
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& rhs)
{
  std::cout << "Matrix: assignment operator" << std::endl;
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

    copy(rhs);
  }

  return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& rhs)
{
  std::cout << "Matrix: move assignment operator" << std::endl;

  if (&rhs != this)
  {
    destroy();
    move(rhs);
  }
  return *this;
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
void Matrix<T>::move(Matrix&& rhs)
{
  m_height = rhs.m_height;
  m_width =  rhs.m_width;
  m_qtyLayers = rhs.m_qtyLayers;
  m_values = rhs.m_values;
  m_lines = rhs.m_lines;

  rhs.m_height = 0;
  rhs.m_width = 0;
  rhs.m_qtyLayers = 0;
  rhs.m_values = 0; // nullptr
  rhs.m_lines = 0; // nullptr
}

template<typename T>
void Matrix<T>::copy(const Matrix& rhs)
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    memcpy(m_values[z][0], rhs.m_values[z][0], m_width * m_height * sizeof(T));
  }
}

template<typename T>
void Matrix<T>::setAllValues(T value)
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    if (sizeof(T) == 1)
    {
      memset(m_lines[z], T, m_width * m_height);
    }
    else
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
}

template<typename T>
void Matrix<T>::setValue(T value, unsigned int x, unsigned int y, unsigned int z)
{
  if (x < m_width && y < m_height && z < m_qtyLayers)
  {
    m_values[z][y][x] = value;
  }
}

template<typename T>
T Matrix<T>::getValue(unsigned int x, unsigned int y, unsigned int z) const
{
  if (x < m_width && y < m_height && z < m_qtyLayers)
  {
    return m_values[z][y][x];
  }
  else
  {
    return 0;
  }
}

template<typename T>
T* Matrix<T>::getLayer(unsigned int z) const
{
  return *(m_values[z]);
}

template<typename T>
void Matrix<T>::setRandomValues()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        // TODO better random generator
        m_values[z][y][x] = rand();
      }
    }
  }
}

template<typename T>
void Matrix<T>::binarize(T threshold)
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        if (m_values[z][y][x] < threshold)
        {
          m_values[z][y][x] = std::numeric_limits<T>::min();
        }
        else
        {
          m_values[z][y][x] = std::numeric_limits<T>::max();
        }
      }
    }
  }
}

template<typename T>
void Matrix<T>::spread()
{
  T maximum = getMaximum();
  T minimum = getMinimum();

  if ((maximum - minimum) == 0)
  {
    // avoid division by zero
    // TODO set all values to max possible value?
    return;
  }

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        if (std::numeric_limits<T>::is_signed)
        {
          // TODO define spread-function for signed types
        }
        else
        {
          if (minimum != 0)
          {
            m_values[z][y][x] -=minimum;
          }
          m_values[z][y][x] = m_values[z][y][x] * std::numeric_limits<T>::max() / (maximum - minimum);
        }
      }
    }
  }
}

template<typename T>
unsigned int Matrix<T>::getWidth() const
{
  return m_width;
}

template<typename T>
unsigned int Matrix<T>::getHeight() const
{
  return m_height;
}

template<typename T>
unsigned int Matrix<T>::getDepth() const
{
  return m_qtyLayers;
}

template<typename T>
T Matrix<T>::getMinimum() const
{
  T minimum = std::numeric_limits<T>::max();
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        if (m_values[z][y][x] < minimum)
        {
          minimum = m_values[z][y][x];
        }
      }
    }
  }
  return minimum;
}

template<typename T>
T Matrix<T>::getMaximum() const
{
  T maximum = std::numeric_limits<T>::min();
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        if (m_values[z][y][x] > maximum)
        {
          maximum = m_values[z][y][x];
        }
      }
    }
  }
  return maximum;
}

template<typename T>
void Matrix<T>::printValuesToConsole(const std::string& description) const
{
  std::cout << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << description << std::endl;
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    std::cout << std::endl << "layer " << z << std::endl;

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
