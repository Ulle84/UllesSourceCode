#include "Image.h"

Image::Image()
{

}

Image::Image( unsigned int width, unsigned int height, unsigned int qtyLayers) :
  Matrix<unsigned char>(width, height, qtyLayers)
{
  
}

