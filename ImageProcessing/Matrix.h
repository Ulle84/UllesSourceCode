#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <typeinfo>
#include <string>
#include <limits>

#include <math.h>

#include <Circle.h>
#include <FreemanCode.h>
#include <Point.h>
#include <Rectangle.h>
#include <PolyLine.h>

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
  unsigned int getDepth() const; // TODO rename getQtyLayers
  T getMinimum() const;
  T getMaximum() const;

  void printValuesToConsole(const std::string& description) const;
  void setIncreasingValues();
  void clear();
  void setAllValues(T value, unsigned int z = 0);
  void setValue(T value, unsigned int x, unsigned int y, unsigned int z = 0);

  T getValue(unsigned int x, unsigned int y, unsigned int z = 0) const;
  T* getLayer(unsigned int z) const; // TODO define return value const, so the matrix values can not be changed!
  T* getColorLayer() const; // TODO remove function - it's only a quick hack!

  void setRandomValues();
  void binarize(T threshold);
  void spread();

  bool isPointInImage(const Point& point); // TODO rename function

  // TODO mark vs. draw vs. set -> one way to define
  void markLine(T value, unsigned int y, unsigned int z = 0);
  void markColumn(T value, unsigned int x, unsigned int z = 0);

  void drawPoint(T value, const Point& point, unsigned int z = 0);
  void drawRectangle(T value, const Rectangle& rectangle, unsigned int z = 0); // TODO bool fill
  void drawLine(T value, const Point& p1, const Point& p2, unsigned int z = 0);
  void drawCircle(T value, const Circle& circle, bool fill = true, unsigned int z = 0);
  void drawFreemanCode(T value, const FreemanCode& freemanCode, unsigned int z = 0);
  void drawPolyLine(T value, const PolyLine& polyLine, unsigned int z = 0);
  void invert();
  
protected:
  T*** m_values;
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_qtyLayers;

private:
  unsigned int minimum(unsigned int value1, unsigned int value2);
  unsigned int maximum(unsigned int value1, unsigned int value2);


  void create();
  void destroy();
  void move(Matrix&& rhs);
  void copy(const Matrix&);

  T** m_lines;
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
  m_width = rhs.m_width;
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
void Matrix<T>::setAllValues(T value, unsigned int z)
{
  if (sizeof(T) == 1)
  {
    memset(m_lines[z], value, m_width * m_height);
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
T* Matrix<T>::getColorLayer() const
{
  unsigned int bufferSize = m_height * m_width * 4;
  T* colorLayer = new T[bufferSize];
  memset(colorLayer, 0, bufferSize);

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      for (unsigned int z = 0; z < m_qtyLayers; z++)
      {
        colorLayer[(y * m_width + x) * 4 + z] = m_values[z][y][x] ;
      }
    }
  }
  return colorLayer;
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
bool Matrix<T>::isPointInImage(const Point &point)
{
  return point.m_x < m_width && point.m_y < m_height;
}

template<typename T>
void Matrix<T>::markLine(T value, unsigned int y, unsigned int z)
{
  if (y >= m_height)
  {
    return;
  }

  if (sizeof(T) == 1)
  {
    memset(m_values[z][y], value, m_width);
  }
  else
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_values[z][y][x] = value;
    }
  }
}

template<typename T>
void Matrix<T>::markColumn(T value, unsigned int x, unsigned int z)
{
  if (x >= m_width)
  {
    return;
  }

  for (unsigned int y = 0; y < m_width; y++)
  {
    m_values[z][y][x] = value;
  }
}

template<typename T>
void Matrix<T>::drawPoint(T value, const Point &point, unsigned int z)
{
  if (point.m_x >= m_width || point.m_y >= m_height)
  {
    return;
  }
  m_values[z][point.m_y][point.m_x] = value;
}

template<typename T>
void Matrix<T>::drawRectangle(T value, const Rectangle &rectangle, unsigned int z)
{
  if ((rectangle.m_topLeftCorner.m_x + rectangle.m_width) >= m_width)
  {
    return;
  }

  if ((rectangle.m_topLeftCorner.m_y + rectangle.m_height) >= m_height)
  {
    return;
  }

  for (unsigned int y = rectangle.m_topLeftCorner.m_y; y < (rectangle.m_topLeftCorner.m_y + rectangle.m_height); y++)
  {
    if (sizeof(T) == 1)
    {
      memset(&(m_values[z][y][rectangle.m_topLeftCorner.m_x]), value, rectangle.m_width);
    }
    else
    {
      for (unsigned int x = rectangle.m_topLeftCorner.m_x; x < (rectangle.m_topLeftCorner.m_x + rectangle.m_width); x++)
      {
        m_values[z][y][x] = value;
      }
    }
  }
}

template<typename T>
void Matrix<T>::drawLine(T value, const Point &p1, const Point &p2, unsigned int z)
{
  if (!isPointInImage(p1) || !isPointInImage(p2))
  {
    return;
  }

  if (p1.m_x == p2.m_x)
  {
    // draw vertical line
    unsigned int min = minimum(p1.m_y, p2.m_y);
    unsigned int max = maximum(p1.m_y, p2.m_y);

    for (unsigned int y = min; y <= max; y++)
    {
      m_values[z][y][p1.m_x] = value;
    }

    return;
  }

  if (p1.m_y == p2.m_y)
  {
    // draw horizontal line
    unsigned int min = minimum(p1.m_x, p2.m_x);
    unsigned int max = maximum(p1.m_x, p2.m_x);

    // TODO memset if sizeof(T) == 1
    for (unsigned int x = min; x <= max; x++)
    {
      m_values[z][p1.m_y][x] = value;
    }

    return;
  }

  // code below copied partially from
  // https://de.wikipedia.org/wiki/Bresenham-Algorithmus#Kompakte_Variante

  int x0 = p1.m_x;
  int y0 = p1.m_y;
  int x1 = p2.m_x;
  int y1 = p2.m_y;

  int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  while(1){
    m_values[z][y0][x0] = value; //setPixel(x0,y0);
    if (x0==x1 && y0==y1) break;
    e2 = 2*err;
    if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

template<typename T>
void Matrix<T>::drawCircle(T value, const Circle &circle, bool fill, unsigned int z)
{
  // code below copied partially from
  // https://en.wikipedia.org/wiki/Midpoint_circle_algorithm

  int x = circle.m_radius;
  int y = 0;
  int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

  while(y <= x)
  {
    if (fill)
    {
      for (int xx = -x; xx <= x; xx++)
      {
        m_values[z][circle.m_center.m_y + y][circle.m_center.m_x + xx] = value; // Octant 1 + Octant 4
        m_values[z][circle.m_center.m_y - y][circle.m_center.m_x + xx] = value; // Octant 5 + Octant 8
      }

      for (int yy = -y; yy <= y; yy++)
      {
        m_values[z][circle.m_center.m_y + x][circle.m_center.m_x + yy] = value; // Octant 2 + Octant 3
        m_values[z][circle.m_center.m_y - x][circle.m_center.m_x + yy] = value; // Octant 6 + Octant 7
      }

      // TODO memset for sizeof(T) == 1
      // TODO improve performance: memset is called "too often" for first/last line in Octant 2 + 3 and Octant 6 + 7
      /*memset(&m_pixels[( y + circle.m_center.m_y) * m_width - x + circle.m_center.m_x], value, 2 * x + 1); //  Octant 1 + Octant 4
      memset(&m_pixels[( x + circle.m_center.m_y) * m_width - y + circle.m_center.m_x], value, 2 * y + 1); //  Octant 2 + Octant 3

      memset(&m_pixels[(-y + circle.m_center.m_y) * m_width - x + circle.m_center.m_x], value, 2 * x + 1); //  Octant 5 + Octant 8
      memset(&m_pixels[(-x + circle.m_center.m_y) * m_width - y + circle.m_center.m_x], value, 2 * y + 1); //  Octant 6 + Octant 7*/
    }
    else
    {
      m_values[z][circle.m_center.m_y + y][circle.m_center.m_x + x] = value; // Octant 1
      m_values[z][circle.m_center.m_y + x][circle.m_center.m_x + y] = value; // Octant 2
      m_values[z][circle.m_center.m_y + x][circle.m_center.m_x - y] = value; // Octant 3
      m_values[z][circle.m_center.m_y + y][circle.m_center.m_x - x] = value; // Octant 4

      m_values[z][circle.m_center.m_y - y][circle.m_center.m_x - x] = value; // Octant 5
      m_values[z][circle.m_center.m_y - x][circle.m_center.m_x - y] = value; // Octant 6
      m_values[z][circle.m_center.m_y - x][circle.m_center.m_x + y] = value; // Octant 7
      m_values[z][circle.m_center.m_y - y][circle.m_center.m_x + x] = value; // Octant 8
    }

    y++;

    if (decisionOver2 <= 0)
    {
      decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
    }
    else
    {
      x--;
      decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
    }
  }
}

template<typename T>
void Matrix<T>::drawFreemanCode(T value, const FreemanCode &freemanCode, unsigned int z)
{
  drawPoint(value, freemanCode.m_startPoint, z);

  unsigned int x = freemanCode.m_startPoint.m_x;
  unsigned int y = freemanCode.m_startPoint.m_y;

  for (auto it = freemanCode.m_directions.begin(); it != freemanCode.m_directions.end(); it++)
  {
    /* 321
     * 4*0
     * 567 */

    switch (*it)
    {
    case 0:
      x++;
      break;
    case 1:
      x++;
      y--;
      break;
    case 2:
      y--;
      break;
    case 3:
      x--;
      y--;
      break;
    case 4:
      x--;
      break;
    case 5:
      x--;
      y++;
      break;
    case 6:
      y++;
      break;
    case 7:
      x++;
      y++;
      break;
    default:
      // should not happen
      break;
    }

    drawPoint(value, Point(x, y), z);

    //m_matrix[y][x] = 255;
  }
}

template<typename T>
void Matrix<T>::drawPolyLine(T value, const PolyLine &polyLine, unsigned int z)
{
  if (polyLine.m_points.size() < 2)
  {
    return;
  }

  auto itPrevious = polyLine.m_points.begin();
  for (auto it = polyLine.m_points.begin(); it != polyLine.m_points.end(); it++)
  {
    if (it == polyLine.m_points.begin())
    {
      continue;
    }

    drawLine(value, *itPrevious, *it, z);

    itPrevious = it;
  }
}

template<typename T>
void Matrix<T>::invert()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        if (std::numeric_limits<T>::is_signed)
        {
          // TODO
        }
        else
        {
          m_values[z][y][x] = std::numeric_limits<T>::max() - m_values[z][y][x];
        }
      }
    }
  }
}

template<typename T>
unsigned int Matrix<T>::minimum(unsigned int value1, unsigned int value2)
{
  return value1 < value2 ? value1 : value2;
}

template<typename T>
unsigned int Matrix<T>::maximum(unsigned int value1, unsigned int value2)
{
  return value1 > value2 ? value1 : value2;
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
