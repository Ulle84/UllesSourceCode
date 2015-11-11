#pragma once

#include <string>

#include "Point.h"
#include "Rectangle.h"

class Image
{
public:
  Image();
  Image(unsigned int width, unsigned int height);
  Image(const Image& rhs);
  ~Image();

  Image& operator= (const Image& rhs);

  void printToConsole(const std::string& description) const;

  unsigned char getPixelValue(unsigned int x, unsigned int y) const;
  unsigned int getHeight() const;
  unsigned int getWidth() const;
  unsigned char** getMatrix() const;
  unsigned char* getPixels() const;
  unsigned char getMinimum() const;
  unsigned char getMaximum() const;

  void setAllPixelValues(unsigned char value);
  void setPixelValue(unsigned int x, unsigned int y, unsigned char value);
  void setIncreasingPixelValues();
  void setRandomPixelValues();

  void dilate(unsigned int filterSize);
  void erode(unsigned int filterSize);
  void filterMean(unsigned int filterSize);

  void binarize(unsigned char threshold);
  void spread();

  bool isPointInImage(const Point& point);

  void markPoint(const Point& point, unsigned char value);
  void markLine(unsigned int lineNumber, unsigned char value);
  void markColumn(unsigned int columnNumber, unsigned char value);
  void markRectangle(const Rectangle& rectangle, unsigned char value);

  void mirrorOnHorizontalAxis();
  void mirrorOnVerticalAxis();
  void rotateBy90DegreeClockwise();
  void rotateBy90DegreeCounterClockwise();
  void rotateBy180Degree();

  friend bool operator== (const Image& image1, const Image& image2);
  friend bool operator!= (const Image& image1, const Image& image2);

private:
  void initPixels();

  unsigned int m_width;
  unsigned int m_height;

  unsigned char* m_pixels;
  unsigned char** m_matrix;
};
