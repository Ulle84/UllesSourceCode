#ifndef IMAGE_H
#define IMAGE_H

#include "Matrix.h"

class Image : public Matrix<unsigned char>
{
public:
  Image();
  Image(unsigned int width, unsigned int height, unsigned int qtyLayers = 1);
};

#endif // IMAGE_H
