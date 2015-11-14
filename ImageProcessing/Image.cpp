#include <iostream>

#include <QDebug>

#include "Image.h"

Image::Image() :
  m_width(5),
  m_height(3)
{
  initPixels();
}

Image::Image(unsigned int width, unsigned int height) :
  m_width(width),
  m_height(height)
{
  initPixels();
}

Image::Image(const Image& rhs)
{
  m_width = rhs.m_width;
  m_height = rhs.m_height;

  m_pixels = new unsigned char [m_width * m_height];
  memcpy(m_pixels, rhs.m_pixels, m_width * m_height);

  m_matrix = new unsigned char*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }
}

Image& Image::operator=(const Image& rhs)
{
  if (&rhs != this)
  {
    if (m_width != rhs.m_width || m_height != rhs.m_height)
    {
      if (m_width * m_height != rhs.m_width * rhs.m_height)
      {
        delete[] m_pixels;
        m_pixels = new unsigned char[rhs.m_width * rhs.m_height];
      }

      if (m_height != rhs.m_height)
      {
        delete[] m_matrix;
        m_matrix = new unsigned char*[rhs.m_height];
      }

      for (unsigned int i = 0; i < rhs.m_height; i++)
      {
        m_matrix[i] = &m_pixels[i * rhs.m_width];
      }

      m_width = rhs.m_width;
      m_height = rhs.m_height;
    }

    memcpy(m_pixels, rhs.m_pixels, m_width * m_height);
  }

  return *this;
}


Image::~Image()
{
  delete[] m_pixels;
  delete[] m_matrix;
}

void Image::initPixels()
{
  m_pixels = new unsigned char[m_width * m_height];
  m_matrix = new unsigned char*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }

  memset(m_pixels, 0, m_width * m_height);
}

void Image::setAllPixelValues(unsigned char value)
{
  memset(m_pixels, value, m_width * m_height);
}

void Image::setPixelValue(unsigned int x, unsigned int y, unsigned char value)
{
  if (x < m_width && y < m_height)
  {
    m_matrix[y][x] = value;
  }
}

unsigned char Image::getPixelValue(unsigned int x, unsigned int y) const
{
  if (x < m_width && y < m_height)
  {
    return m_matrix[y][x];
  }
  else
  {
    return 0;
  }
}

unsigned int Image::getHeight() const
{
  return m_height;
}

unsigned int Image::getWidth() const
{
  return m_width;
}

unsigned char** Image::getMatrix() const
{
  return m_matrix;
}

unsigned char* Image::getPixels() const
{
  return m_pixels;
}

unsigned char Image::getMinimum() const
{
  unsigned char minimum = 255;
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    if(m_pixels[i] < minimum)
    {
      minimum = m_pixels[i];
    }
  }
  return minimum;
}

unsigned char Image::getMaximum() const
{
  unsigned char maximum = 0;
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    if(m_pixels[i] > maximum)
    {
      maximum = m_pixels[i];
    }
  }
  return maximum;
}

void Image::setIncreasingPixelValues()
{
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    m_pixels[i] = i % 256;
  }
}

void Image::setRandomPixelValues()
{
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    m_pixels[i] = rand() % 256;
  }
}

void Image::dilate(unsigned int filterSize)
{
  Image original(*this);

  int offset = filterSize / 2;

  for (unsigned int y = offset; y < (m_height - offset); y++)
  {
    for (unsigned int x = offset; x < (m_width - offset); x++)
    {
      unsigned char maximum = 0;
      for (int fy = -offset; fy <= offset; fy++)
      {
        for (int fx = -offset; fx <= offset; fx++)
        {
          if (original.m_matrix[y+fy][x+fx] > maximum)
          {
            maximum = original.m_matrix[y+fy][x+fx];
          }
        }
      }
      m_matrix[y][x] = maximum;
    }
  }
}

void Image::erode(unsigned int filterSize)
{
  Image original(*this);

  int offset = filterSize / 2;

  for (unsigned int y = offset; y < (m_height - offset); y++)
  {
    for (unsigned int x = offset; x < (m_width - offset); x++)
    {
      unsigned char minimum = 255;
      for (int fy = -offset; fy <= offset; fy++)
      {
        for (int fx = -offset; fx <= offset; fx++)
        {
          if (original.m_matrix[y+fy][x+fx] < minimum)
          {
            minimum = original.m_matrix[y+fy][x+fx];
          }
        }
      }
      m_matrix[y][x] = minimum;
    }
  }
}

void Image::doOpening(unsigned int filterSize)
{
  erode(filterSize);
  dilate(filterSize);
}

void Image::doClosing(unsigned int filterSize)
{
  dilate(filterSize);
  erode(filterSize);
}

void Image::filterMean(unsigned int filterSize)
{
  Image original(*this);

  int offset = filterSize / 2;
  double calculatedValue;

  for (unsigned int y = offset; y < (m_height - offset); y++)
  {
    for (unsigned int x = offset; x < (m_width - offset); x++)
    {
      calculatedValue = 0;
      for (int fy = -offset; fy <= offset; fy++)
      {
        for (int fx = -offset; fx <= offset; fx++)
        {
          calculatedValue += original.m_matrix[y+fy][x+fx];
        }
      }
      calculatedValue /= (filterSize * filterSize);
      m_matrix[y][x] = calculatedValue + 0.5;
    }
  }
}

void Image::binarize(unsigned char threshold)
{
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    if (m_pixels[i] <= threshold)
    {
      m_pixels[i] = 0;
    }
    else
    {
      m_pixels[i] = 255;
    }
  }
}

void Image::spread()
{
  unsigned char maximum = getMaximum();
  unsigned char minimum = getMinimum();

  if ((maximum - minimum) == 0)
  {
    return;
  }

  // map minimum to zero
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    m_pixels[i] -= minimum;
  }

  // spread
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    m_pixels[i] = m_pixels[i] * 255 / (maximum - minimum);
  }
}

bool Image::isPointInImage(const Point &point)
{
  return point.m_x < m_width && point.m_y < m_height;
}

void Image::drawPoint(const Point &point, unsigned char value)
{
  if (isPointInImage(point))
  {
    m_matrix[point.m_y][point.m_x] = value;
  }
}

void Image::markLine(unsigned int lineNumber, unsigned char value)
{
  if (lineNumber >= m_height)
  {
    return;
  }

  memset(&m_pixels[lineNumber * m_width], value, m_width);
}

void Image::markColumn(unsigned int columnNumber, unsigned char value)
{
  if (columnNumber >= m_width)
  {
    return;
  }

  for (unsigned int y = 0; y < m_height; y++)
  {
    m_matrix[y][columnNumber] = value;
  }
}

void Image::drawRectangle(const Rectangle &rectangle, unsigned char value)
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
    memset(&m_pixels[y * m_width + rectangle.m_topLeftCorner.m_x], value, rectangle.m_width);
  }
}

void Image::drawCircle(const Point &center, unsigned int radius, unsigned char value, bool fill)
{
  // code below copied partially from
  // https://en.wikipedia.org/wiki/Midpoint_circle_algorithm

  int x = radius;
  int y = 0;
  int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

  while(y <= x)
  {
    if (fill)
    {
      // TODO improve performance: memset is called "too often" for Octant 2 + 3 and Octant 6 + 7
      memset(&m_pixels[( y + center.m_y) * m_width - x + center.m_x], value, 2 * x + 1); //  Octant 1 + Octant 4
      memset(&m_pixels[( x + center.m_y) * m_width - y + center.m_x], value, 2 * y + 1); //  Octant 2 + Octant 3

      memset(&m_pixels[(-y + center.m_y) * m_width - x + center.m_x], value, 2 * x + 1); //  Octant 5 + Octant 8
      memset(&m_pixels[(-x + center.m_y) * m_width - y + center.m_x], value, 2 * y + 1); //  Octant 6 + Octant 7
    }
    else
    {
      m_matrix[ y + center.m_y][ x + center.m_x] = value; // Octant 1
      m_matrix[ x + center.m_y][ y + center.m_x] = value; // Octant 2
      m_matrix[ x + center.m_y][-y + center.m_x] = value; // Octant 3
      m_matrix[ y + center.m_y][-x + center.m_x] = value; // Octant 4

      m_matrix[-y + center.m_y][-x + center.m_x] = value; // Octant 5
      m_matrix[-x + center.m_y][-y + center.m_x] = value; // Octant 6
      m_matrix[-x + center.m_y][ y + center.m_x] = value; // Octant 7
      m_matrix[-y + center.m_y][ x + center.m_x] = value; // Octant 8
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

void Image::mirrorOnHorizontalAxis()
{
  Image original(*this);

  for (unsigned int y = 0; y < m_height; y++)
  {
    memcpy(&m_matrix[y][0], &(original.m_matrix[m_height - y - 1][0]), m_width);
  }
}

void Image::mirrorOnVerticalAxis()
{
  Image original(*this);

  for (unsigned int x = 0; x < m_width; x++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      m_matrix[y][x] = original.m_matrix[y][m_width - x - 1];
    }
  }
}

void Image::rotateBy90DegreeClockwise()
{
  Image original(*this);

  m_width = original.m_height;
  m_height = original.m_width;

  delete[] m_matrix;
  m_matrix = new unsigned char*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_matrix[y][x] = original.m_matrix[original.m_height - x - 1][y];
    }
  }
}

void Image::rotateBy90DegreeCounterClockwise()
{
  Image original(*this);

  m_width = original.m_height;
  m_height = original.m_width;

  delete[] m_matrix;
  m_matrix = new unsigned char*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_matrix[y][x] = original.m_matrix[x][original.m_width - y - 1];
    }
  }
}

void Image::rotateBy180Degree()
{
  Image original(*this);

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_matrix[y][x] = original.m_matrix[m_height - y - 1][m_width - x - 1];
    }
  }
}

void Image::printToConsole(const std::string& description) const
{
  std::cout << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << description << std::endl;

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      if (m_matrix[y][x] < 10)
      {
        std::cout << " ";
      }

      if (m_matrix[y][x] < 100)
      {
        std::cout << " ";
      }

      std::cout << (int) m_matrix[y][x] << " ";
    }

    std::cout << std::endl;
  }
}

bool operator== (const Image& image1, const Image& image2)
{
  bool equal = true;

  equal &= image1.m_width  == image2.m_width;
  equal &= image1.m_height == image2.m_height;

  if (equal)
  {
    equal &= memcmp(image1.m_pixels, image2.m_pixels, image1.m_width * image1.m_height) == 0;
  }

  return equal;
}

bool operator!= (const Image& image1, const Image& image2)
{
  return !(image1 == image2);
}
