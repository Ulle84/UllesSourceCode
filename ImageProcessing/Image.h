#pragma once

#include <string>

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

  void setAllPixelValues(unsigned char value);
  void setPixelValue(unsigned int x, unsigned int y, unsigned char value);
  void setIncreasingPixelValues();
  void setRandomPixelValues();

  void dilate(unsigned int filterSize);
  void erode(unsigned int filterSize);
  void filterMean(unsigned int filterSize);

  void binarize(unsigned char threshold);

  friend bool operator== (const Image& image1, const Image& image2);
  friend bool operator!= (const Image& image1, const Image& image2);

private:
  void initPixels();

  unsigned int m_width;
  unsigned int m_height;

  unsigned char* m_pixels;
  unsigned char** m_matrix;
};
