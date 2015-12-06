#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <limits>
#include <typeinfo>
#include <string>
#include <vector>

#include <math.h>

#include <Circle.h>
#include <FreemanCode.h>
#include <Point.h>
#include <Rectangle.h>
#include <PolyLine.h>

#define PI 3.14159265359

// TODO rename this header to Base.h? Here ist not only Matrix defined anymore
// TODO use const wherever possible
// TODO iterate over pointer instead using for-loop with index -> shuold have better performance
// TODO check wrong z values everywhere
// TODO WriteMutex
// TODO with % 4 !== 0
// TODO m_referencePoint?

class Filter;
class StructuringElement;

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
  unsigned int getQtyLayers() const;
  
  T getMinimum() const;
  T getMaximum() const;

  T getValue(unsigned int x, unsigned int y, unsigned int z = 0) const;
  T*** getValues() const; // TODO const, so the pointer-adress can not be changed
  double getSumOfAllValues(unsigned int z = 0) const;
  const T* getLayer(unsigned int z) const;
  const T* getSingleLayer(std::vector<unsigned int> layerIndices) const;
  std::vector<unsigned long long> getHistogram();

  void setIncreasingValues();
  void setRandomValues();
  void setGaussianValues(unsigned int z = 0);
  void setBinomialValues(unsigned int z = 0);
  void setAllValues(T value, unsigned int z = 0);
  void setValue(T value, unsigned int x, unsigned int y, unsigned int z = 0);
  void setSingleLayer(T* buffer, std::vector<unsigned int> layerIndices);
  void setRow(T value, unsigned int y, unsigned int z = 0);
  void setColumn(T value, unsigned int x, unsigned int z = 0);
  void setPoint(T value, const Point& point, unsigned int z = 0);
  void setRectangle(T value, const Rectangle& rectangle, bool fill = true, unsigned int z = 0);
  void setLine(T value, const Point& p1, const Point& p2, unsigned int z = 0);
  void setCircle(T value, const Circle& circle, bool fill = true, unsigned int z = 0);
  void setFreemanCode(T value, const FreemanCode& freemanCode, unsigned int z = 0);
  void setPolyLine(T value, const PolyLine& polyLine, unsigned int z = 0);
  void setHistogram(const std::vector<unsigned long long>& histogram, unsigned int z = 0);

  void applyFilter(const Filter* filter, unsigned int z = 0);
  void binarize(T threshold);
  void spread();
  void clear();
  void invert();

  // morphology
  void erode(const StructuringElement* structuringElement, unsigned int z = 0);
  void dilate(const StructuringElement* structuringElement, unsigned int z = 0);
  void open(const StructuringElement* structuringElement, unsigned int z = 0);
  void close(const StructuringElement* structuringElement, unsigned int z = 0);
  void applyConservativeSmoothingFilter(const StructuringElement *structuringElement, unsigned int z = 0);

  void mirrorOnHorizontalAxis();
  void mirrorOnVerticalAxis();
  void rotateBy90DegreeClockwise();
  void rotateBy90DegreeCounterClockwise();
  void rotateBy180Degree();

  Matrix<T> crop(const Rectangle &cropRegion);
  Matrix<T> doPolarTransformation(const Circle& circle);

  void applyLookUpTable(const std::vector<T> &lookUpTable);
  //void filter(const FilterMask& filterMask);

  bool isPointInsideImage(const Point& point);
  bool isRectangleInsideImage(const Rectangle& rectangle);
  bool isCircleInsideImage(const Circle& circle);

  void printValuesToConsole(const std::string& description) const;
  
protected:
  T*** m_values;
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_qtyLayers;

private:
  unsigned int minimum(unsigned int value1, unsigned int value2);
  unsigned int maximum(unsigned int value1, unsigned int value2);
  unsigned int calculateBinomialCoefficient(unsigned int n, unsigned int k);

  void create();
  void createRowBeginVector();
  void createLayers();
  void destroy();
  void destroyRowBeginVector();
  void destroyLayers();
  void copy(const Matrix&);

  T** m_layers;

  friend bool operator== (const Matrix<T>& matrix1, const Matrix<T>& matrix2);
  friend bool operator!= (const Matrix<T>& matrix1, const Matrix<T>& matrix2);
};

// TBD type short?
class Filter : public Matrix<short>
{
public:
  Filter(unsigned width, unsigned height) : Matrix<short>(width, height){m_preFactor = 1.0; m_referencePoint.m_x = width / 2; m_referencePoint.m_y = height / 2; m_shiftResultValues = false; m_invertNegativeResultValues;}

  void setReferencePoint(const Point& referencePoint) {m_referencePoint = referencePoint;}
  Point getReferencePoint() const {return m_referencePoint;}

  void setPreFactor(double preFactor) {m_preFactor = preFactor;}
  double getPreFactor() const {return m_preFactor;}

  bool getShiftResultValues() const {return m_shiftResultValues;}
  void setShiftResultValues(bool shiftResultValues) {m_shiftResultValues = shiftResultValues;}

  bool getInvertNegativeResultValues() const {return m_invertNegativeResultValues;}
  void setInvertNegativeResultValues(bool invertNegativeResultValues) {m_invertNegativeResultValues = invertNegativeResultValues;}

private:
  Filter(){}

  bool m_shiftResultValues;
  bool m_invertNegativeResultValues;
  double m_preFactor;
  Point m_referencePoint;
};

class StructuringElement : public Matrix<bool>
{
public:
  StructuringElement(unsigned width, unsigned height) : Matrix<bool>(width, height){m_referencePoint.m_x = width / 2; m_referencePoint.m_y = height / 2; setAllValues(true);}

  void setReferencePoint(const Point& referencePoint) {m_referencePoint = referencePoint;}
  Point getReferencePoint() const {return m_referencePoint;}

private:
  StructuringElement(){}

  Point m_referencePoint;
};

template<typename T>
void Matrix<T>::setSingleLayer( T* buffer, std::vector<unsigned int> layerIndices )
{
  unsigned int qtyLayerIndices = layerIndices.size();
  
  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      for (unsigned int z = 0; z < qtyLayerIndices; z++)
      {
        m_values[layerIndices[z]][y][x] = buffer[(y * m_width + x) * qtyLayerIndices + z];
      }
    }
  }
}

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

  m_height = rhs.m_height;
  m_width = rhs.m_width;
  m_qtyLayers = rhs.m_qtyLayers;
  m_values = rhs.m_values;
  m_layers = rhs.m_layers;

  rhs.m_height = 0;
  rhs.m_width = 0;
  rhs.m_qtyLayers = 0;
  rhs.m_values = 0; // nullptr
  rhs.m_layers = 0; // nullptr
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
  createLayers();
  createRowBeginVector();
}

template<typename T>
void Matrix<T>::createLayers()
{
  m_layers = new T*[m_qtyLayers];

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    m_layers[z] = new T[m_width * m_height];
  }
}

template<typename T>
void Matrix<T>::createRowBeginVector()
{
  m_values = new T**[m_qtyLayers];

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    m_values[z] = new T*[m_height];

    for (unsigned int y = 0; y < m_height; y++)
    {
      m_values[z][y] = &m_layers[z][y * m_width];
    }
  }
}

template<typename T>
void Matrix<T>::destroy()
{
  destroyRowBeginVector();
  destroyLayers();
}

template<typename T>
void Matrix<T>::destroyLayers()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    delete[] m_layers[z];
  }

  delete[] m_layers;
}

template<typename T>
void Matrix<T>::destroyRowBeginVector()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    delete[] m_values[z];
  }

  delete[] m_values;
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

    m_height = rhs.m_height;
    m_width = rhs.m_width;
    m_qtyLayers = rhs.m_qtyLayers;
    m_values = rhs.m_values;
    m_layers = rhs.m_layers;

    rhs.m_height = 0;
    rhs.m_width = 0;
    rhs.m_qtyLayers = 0;
    rhs.m_values = 0; // nullptr
    rhs.m_layers = 0; // nullptr
  }
  return *this;
}

template<typename T>
void Matrix<T>::clear()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    memset(m_layers[z], 0, m_width * m_height * sizeof(T));
  }
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
  if (z >= m_qtyLayers)
  {
    return;
  }

  if (sizeof(T) == 1)
  {
    memset(m_layers[z], value, m_width * m_height);
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
T ***Matrix<T>::getValues() const
{
  return m_values;
}

template<typename T>
double Matrix<T>::getSumOfAllValues(unsigned int z) const
{
  double sum = 0.0;

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      sum += m_values[z][y][x];
    }
  }

  return sum;
}

template<typename T>
const T* Matrix<T>::getLayer(unsigned int z) const
{
  return *(m_values[z]);
}

template<typename T>
const T* Matrix<T>::getSingleLayer(std::vector<unsigned int> layerIndices) const
{
  unsigned int qtyLayerIndices = layerIndices.size();
  unsigned int bufferSize = m_height * m_width * qtyLayerIndices;
  T* singleLayer = new T[bufferSize]; // TODO avoid memory leak -> recycle buffer if possible

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      for (unsigned int z = 0; z < qtyLayerIndices; z++)
      {
        singleLayer[(y * m_width + x) * qtyLayerIndices + z] = m_values[layerIndices[z]][y][x] ;
      }
    }
  }

  return singleLayer;
}

template<typename T>
std::vector<unsigned long long> Matrix<T>::getHistogram()
{
  if (std::numeric_limits<T>::is_signed)
  {
    // TODO how to implement negative values?
    return std::vector<unsigned long long>(0);
  }

  // TODO do not accept T to be floating point value

  std::vector<unsigned long long> histogram(std::numeric_limits<T>::max() + 1); // TODO verify for big data types like long etc.
  std::fill(histogram.begin(), histogram.end(), 0);

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        histogram[m_values[z][y][x]]++;
      }
    }
  }

  return histogram;
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
        // NTH better random generator
        m_values[z][y][x] = rand();
      }
    }
  }
}

template<typename T>
void Matrix<T>::setGaussianValues(unsigned int z)
{
  // TODO
}

/* 1 2 1
 * 2 4 2
 * 1 2 1 */

template<typename T>
void Matrix<T>::setBinomialValues(unsigned int z)
{
  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_values[z][y][x] = calculateBinomialCoefficient(m_width - 1, x) * calculateBinomialCoefficient(m_height - 1, y);
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
    // TBD set all values to max possible value?
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
bool Matrix<T>::isPointInsideImage(const Point &point)
{
  return point.m_x < m_width && point.m_y < m_height;
}

template<typename T>
bool Matrix<T>::isRectangleInsideImage(const Rectangle& rectangle)
{
  bool rectangleInImage = true;

  rectangleInImage &= ((rectangle.m_topLeftCorner.m_x + rectangle.m_width) < m_width);
  rectangleInImage &= ((rectangle.m_topLeftCorner.m_y + rectangle.m_height) < m_height);

  return rectangleInImage;
}

template<typename T>
bool Matrix<T>::isCircleInsideImage(const Circle &circle)
{
  bool circleInImage = true;

  circleInImage &= ((circle.m_center.m_x - circle.m_radius) >=  0);
  circleInImage &= ((circle.m_center.m_y - circle.m_radius) >=  0);

  circleInImage &= ((circle.m_center.m_x + circle.m_radius) <  m_width);
  circleInImage &= ((circle.m_center.m_y + circle.m_radius) <  m_height);

  return circleInImage;
}

template<typename T>
void Matrix<T>::setRow(T value, unsigned int y, unsigned int z)
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
void Matrix<T>::setColumn(T value, unsigned int x, unsigned int z)
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
void Matrix<T>::setPoint(T value, const Point &point, unsigned int z)
{
  if (point.m_x >= m_width || point.m_y >= m_height)
  {
    return;
  }
  m_values[z][point.m_y][point.m_x] = value;
}

template<typename T>
void Matrix<T>::setRectangle(T value, const Rectangle &rectangle, bool fill, unsigned int z)
{
  if (!isRectangleInsideImage(rectangle))
  {
    return;
  }

  if (fill)
  {
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
  else
  {
    for (unsigned int x = rectangle.m_topLeftCorner.m_x; x < (rectangle.m_topLeftCorner.m_x + rectangle.m_width); x++)
    {
      // TODO use memset if sizeof(T) == 1
      m_values[z][rectangle.m_topLeftCorner.m_y][x] = value;
      m_values[z][rectangle.m_topLeftCorner.m_y + rectangle.m_height - 1][x] = value;
    }
    
    for (unsigned int y = rectangle.m_topLeftCorner.m_y + 1; y < (rectangle.m_topLeftCorner.m_y + rectangle.m_height - 1); y++)
    {
      m_values[z][y][rectangle.m_topLeftCorner.m_x] = value;
      m_values[z][y][rectangle.m_topLeftCorner.m_x + rectangle.m_width - 1] = value;
    }
  }
}

template<typename T>
void Matrix<T>::setLine(T value, const Point &p1, const Point &p2, unsigned int z)
{
  if (!isPointInsideImage(p1) || !isPointInsideImage(p2))
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

    // IP memset if sizeof(T) == 1
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
    m_values[z][y0][x0] = value;
    if (x0==x1 && y0==y1) break;
    e2 = 2*err;
    if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

template<typename T>
void Matrix<T>::setCircle(T value, const Circle &circle, bool fill, unsigned int z)
{
  if (z >= m_qtyLayers)
  {
    return;
  }

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

      // IP memset for sizeof(T) == 1
      // IP improve performance: memset is called "too often" for first/last line in Octant 2 + 3 and Octant 6 + 7
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
void Matrix<T>::setFreemanCode(T value, const FreemanCode &freemanCode, unsigned int z)
{
  setPoint(value, freemanCode.m_startPoint, z);

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

    setPoint(value, Point(x, y), z);
  }
}

template<typename T>
void Matrix<T>::setPolyLine(T value, const PolyLine &polyLine, unsigned int z)
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

    setLine(value, *itPrevious, *it, z);

    itPrevious = it;
  }
}

template<typename T>
void Matrix<T>::setHistogram(const std::vector<unsigned long long> &histogram, unsigned int z)
{
  clear();

  unsigned int barWidth = m_width / histogram.size();

  unsigned long long maxValue = std::numeric_limits<unsigned long long>::min();

  // IP use iterator
  for (unsigned long long i = 0; i < histogram.size(); i++)
  {
    if (histogram[i] > maxValue)
    {
      maxValue = histogram[i];
    }
  }

  for (unsigned long long i = 0; i < histogram.size(); i++)
  {
    unsigned int barHeight = histogram[i] * m_height * 1.0 / maxValue;
    for (unsigned int j = 0; j < barWidth; j++)
    {
      setLine(std::numeric_limits<unsigned long long>::max(), Point(i * barWidth + j, m_height - 1), Point(i * barWidth + j, m_height - barHeight), z);
    }
  }
}

template<typename T>
void Matrix<T>::applyFilter(const Filter *filter, unsigned int z)
{
  Matrix<T> original(*this);

  short*** filterValues = filter->getValues();

  unsigned int offsetLeft = filter->getReferencePoint().m_x;
  unsigned int offsetTop = filter->getReferencePoint().m_y;
  unsigned int offsetRight = filter->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = filter->getHeight() - offsetTop - 1;

  double calculatedValue;
  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      calculatedValue = 0;
      for (unsigned int fy = 0; fy < filter->getHeight(); fy++)
      {
        for (unsigned int fx = 0; fx < filter->getWidth(); fx++)
        {
          calculatedValue += original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft] * filterValues[0][fy][fx];
        }
      }
      calculatedValue *= filter->getPreFactor();
      calculatedValue > 0 ? calculatedValue += 0.5 : calculatedValue -= 0.5;

      if (filter->getShiftResultValues())
      {
        calculatedValue += ((std::numeric_limits<T>::max() - std::numeric_limits<T>::min()) / 2);
      }

      if (filter->getInvertNegativeResultValues())
      {
        if (calculatedValue < 0)
        {
          calculatedValue *= -1;
        }
      }

      if (calculatedValue < std::numeric_limits<T>::min())
      {
        calculatedValue = std::numeric_limits<T>::min();
      }

      if (calculatedValue > std::numeric_limits<T>::max())
      {
        calculatedValue = std::numeric_limits<T>::max();
      }

      m_values[z][y][x] = calculatedValue;
    }
  }
}

template<typename T>
void Matrix<T>::applyConservativeSmoothingFilter(const StructuringElement *structuringElement, unsigned int z)
{
  // look all values in structuringElement (except for reference point)
  // define minimum and maximum
  // if value at reference point is smaller than the minimum, the value is set to the minimum
  // if value at reference point is bigger than the maximum, the value is set to the maximum
  // see: http://homepages.inf.ed.ac.uk/rbf/HIPR2/csmooth.htm

  Matrix<T> original(*this);

  bool*** structuringElementValues = structuringElement->getValues();

  unsigned int offsetLeft = structuringElement->getReferencePoint().m_x;
  unsigned int offsetTop = structuringElement->getReferencePoint().m_y;
  unsigned int offsetRight = structuringElement->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = structuringElement->getHeight() - offsetTop - 1;

  T minimum;
  T maximum;
  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      minimum = std::numeric_limits<T>::max();
      maximum = std::numeric_limits<T>::min();

      if (x == 3 && y == 3)
      {

        std::cout << "minimum: " << (int)minimum << std::endl;
        std::cout << "maximum: " << (int)maximum << std::endl;
      }

      for (unsigned int fy = 0; fy < structuringElement->getHeight(); fy++)
      {
        for (unsigned int fx = 0; fx < structuringElement->getWidth(); fx++)
        {
          bool onReferencePoint = (fx == offsetLeft && fy == offsetTop);

          if (structuringElementValues[0][fy][fx] && !onReferencePoint)
          {
            if (original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft] < minimum)
            {
              minimum = original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft];
            }
            if (original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft] > maximum)
            {
              maximum = original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft];
            }
          }
        }
      }

      if (original.m_values[z][y][x] < minimum)
      {
        m_values[z][y][x] = minimum;
      }

      if (original.m_values[z][y][x] > maximum)
      {
        m_values[z][y][x] = maximum;
      }
    }
  }
}

template<typename T>
void Matrix<T>::erode(const StructuringElement *structuringElement, unsigned int z)
{
  Matrix<T> original(*this);

  bool*** structuringElementValues = structuringElement->getValues();

  unsigned int offsetLeft = structuringElement->getReferencePoint().m_x;
  unsigned int offsetTop = structuringElement->getReferencePoint().m_y;
  unsigned int offsetRight = structuringElement->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = structuringElement->getHeight() - offsetTop - 1;

  T minimum;
  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      minimum = std::numeric_limits<T>::max();

      for (unsigned int fy = 0; fy < structuringElement->getHeight(); fy++)
      {
        for (unsigned int fx = 0; fx < structuringElement->getWidth(); fx++)
        {
          if (structuringElementValues[0][fy][fx] && original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft] < minimum)
          {
            minimum = original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft];
          }
        }
      }
      m_values[z][y][x] = minimum;
    }
  }
}

template<typename T>
void Matrix<T>::dilate(const StructuringElement *structuringElement, unsigned int z)
{
  Matrix<T> original(*this);

  bool*** structuringElementValues = structuringElement->getValues();

  unsigned int offsetLeft = structuringElement->getReferencePoint().m_x;
  unsigned int offsetTop = structuringElement->getReferencePoint().m_y;
  unsigned int offsetRight = structuringElement->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = structuringElement->getHeight() - offsetTop - 1;

  T maximum;
  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      maximum = std::numeric_limits<T>::min();

      for (unsigned int fy = 0; fy < structuringElement->getHeight(); fy++)
      {
        for (unsigned int fx = 0; fx < structuringElement->getWidth(); fx++)
        {
          if (structuringElementValues[0][fy][fx] && original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft] > maximum)
          {
            maximum = original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft];
          }
        }
      }

      m_values[z][y][x] = maximum;
    }
  }
}

template<typename T>
void Matrix<T>::open(const StructuringElement *structuringElement, unsigned int z)
{
  erode(structuringElement, z);
  dilate(structuringElement, z);
}

template<typename T>
void Matrix<T>::close(const StructuringElement *structuringElement, unsigned int z)
{
  dilate(structuringElement, z);
  erode(structuringElement, z);
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
void Matrix<T>::mirrorOnHorizontalAxis()
{
  Matrix<T> original(*this);

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      memcpy(&m_values[z][y][0], &(original.m_values[z][m_height - y - 1][0]), m_width * sizeof(T));
    }
  }
}

template<typename T>
void Matrix<T>::mirrorOnVerticalAxis()
{
  Matrix<T> original(*this);
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      for (unsigned int y = 0; y < m_height; y++)
      {
        m_values[z][y][x] = original.m_values[z][y][m_width - x - 1];
      }
    }
  }
}

template<typename T>
void Matrix<T>::rotateBy90DegreeClockwise()
{
  Matrix<T> original(*this);

  m_width = original.m_height;
  m_height = original.m_width;

  if (m_width != m_height)
  {
    destroyRowBeginVector();
    createRowBeginVector();
  }

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        m_values[z][y][x] = original.m_values[z][original.m_height - x - 1][y];
      }
    }
  }
}

template<typename T>
void Matrix<T>::rotateBy90DegreeCounterClockwise()
{
  Matrix<T> original(*this);

  m_width = original.m_height;
  m_height = original.m_width;

  if (m_width != m_height)
  {
    destroyRowBeginVector();
    createRowBeginVector();
  }

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        m_values[z][y][x] = original.m_values[z][x][original.m_width - y - 1];
      }
    }
  }
}

template<typename T>
void Matrix<T>::rotateBy180Degree()
{
  Matrix<T> original(*this);
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      for (unsigned int y = 0; y < m_height; y++)
      {
        m_values[z][y][x] = original.m_values[z][m_height - y - 1][m_width - x - 1];
      }
    }
  }
}

template<typename T>
Matrix<T> Matrix<T>::crop(const Rectangle& cropRegion)
{
  if (!isRectangleInsideImage(cropRegion))
  {
    return Matrix<T>();
  }

  Matrix<T> cropped(cropRegion.m_width, cropRegion.m_height, m_qtyLayers);


  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < cropRegion.m_height; y++)
    {
      memcpy(cropped.m_values[z][y], &m_values[z][y+cropRegion.m_topLeftCorner.m_y][cropRegion.m_topLeftCorner.m_x], cropRegion.m_width * sizeof(T));
    }
  }

  return cropped;
}

template<typename T>
Matrix<T> Matrix<T>::doPolarTransformation(const Circle &circle)
{
  if (!isCircleInsideImage(circle))
  {
    return Matrix<T>(1, 1);
  }

  unsigned int circumference = circle.m_radius * 2 * 3.14159265359 + 0.5;

  int width = circumference;

  if (width % 4 != 0)
  {
    width += (4 - (width % 4)); // round up -> width % 4 needs to be zero!
  }

  Matrix<T> calculated(width, circle.m_radius, m_qtyLayers); // TODO correct sizes

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < circle.m_radius; y++) // radius
    {
      for (unsigned int x = 0; x < circumference; x++) // angle
      {
        // TODO improve performace -> avoid duplicated calculations -> avoid conversions

        int angle = x * 360.0 / circumference;
        int radius = y;

        int xx = radius * cos(angle * PI / 180.0);
        int yy = radius * sin(angle * PI / 180.0);

        calculated.m_values[z][y][x] = m_values[z][yy + circle.m_center.m_y][xx + circle.m_center.m_x];
      }
    }
  }

  return calculated;
}

template<typename T>
void Matrix<T>::applyLookUpTable(const std::vector<T>& lookUpTable)
{
  if (std::numeric_limits<T>::is_signed)
  {
    // TODO how to define a LUT for negative values?
    return;
  }

  if (lookUpTable.size() < std::numeric_limits<T>::max() + 1)
  {
    // LUT not fully defined
    std::cout << "LUT not fully defined" << std::endl;
    return;
  }

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        m_values[z][y][x] = lookUpTable[m_values[z][y][x]];
      }
    }
  }
}

/*template<typename T>
void Matrix<T>::filter(const FilterMask &filterMask)
{

}*/

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
unsigned int Matrix<T>::calculateBinomialCoefficient(unsigned int n, unsigned int k)
{
  if (k > n)
  {
    return 0;
  }

  // calculate n over k
  double binomialCoefficient = 1;

  for (unsigned int i = 1; i <= k; i++)
  {
    binomialCoefficient *= ((n + 1.0 - i) / i);
  }

  return binomialCoefficient;
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
unsigned int Matrix<T>::getQtyLayers() const
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
        if (m_values[z][y][x] < 1000)
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

template<typename T>
bool operator== (const Matrix<T>& matrix1, const Matrix<T>& matrix2)
{
  // TODO this operator is not called - why???
  std::cout << "== operator" << std::endl;

  bool equal = true;

  equal &= matrix1.m_width  == matrix2.m_width;
  equal &= matrix1.m_height == matrix2.m_height;
  equal &= matrix1.m_qtyLayers == matrix2.m_qtyLayers;

  if (equal)
  {
    for (unsigned int z = 0; z < matrix1.m_qtyLayers; z++)
    {
      equal &= (memcmp(matrix1.m_layers[z], matrix2.m_layers[z], matrix1.m_width * matrix1.m_height * sizeof(T)) == 0);
    }
  }

  return equal;
}

template<typename T>
bool operator!= (const Matrix<T>& matrix1, const Matrix<T>& matrix2)
{
  return !(matrix1 == matrix2);
}

// implement function below, if you need all permutations of filter-type and image-type
/*template<typename F, typename M>
void filterMatrix(Matrix<M>* matrix, Matrix<F>* filter, const Point& referencePoint, double preFactor = 1.0, unsigned z = 0)
{
  M*** m = matrix->getValues();
  F*** f = filter->getValues();

  for (unsigned int y = 0; y < matrix->getHeight(); y++)
  {
    for (unsigned int x = 0; x < matrix->getWidth(); x++)
    {
      m[z][y][x] = f[0][referencePoint.m_y][referencePoint.m_x];
    }
  }
}*/

/* iterate over all values
for (unsigned int z = 0; z < m_qtyLayers; z++)
{
  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_values[z][y][x] = ;
    }
  }
}
*/

#endif // MATRIX_H
