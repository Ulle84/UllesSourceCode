#ifndef IMAGET_H
#define IMAGET_H

#include <iostream>
#include <string>

#include "Point.h"
#include "Rectangle.h"
#include "Circle.h"
#include "FilterMask.h"

template<class T> class ImageT
{
public:
  ImageT();
  ImageT(unsigned int width, unsigned int height);
  ~ImageT();

  void printToConsole(const std::string& description) const;
  unsigned char sizeOfOnePixelInBytes() const;
  T getMaximumValue() const;

  void setIncreasingPixelValues();

private:
  unsigned int m_width;
  unsigned int m_height;

  T* m_pixels;
  T** m_matrix;
};

typedef ImageT<unsigned char> ImageUC;
//typedef ImageUC Image;
typedef ImageT<unsigned int> ImageUI;

// NOTE: if you want to support ALL data-types (not only the ones defined in cpp file)
// you have to define all functions with template parameters inline

#endif // IMAGET_H
