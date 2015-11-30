#include <limits>

#include <QDebug>

#include "ImageT.h"

template<class T> ImageT<T>::ImageT() :
  m_width(4),
  m_height(4)
{
  m_pixels = new T[m_width * m_height];
  m_matrix = new T*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }

  memset(m_pixels, 0, m_width * m_height * sizeof(T));
}

template<class T> ImageT<T>::ImageT(unsigned int width, unsigned int height) :
  m_width(width),
  m_height(height)
{
  m_pixels = new T[m_width * m_height];
  m_matrix = new T*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }

  memset(m_pixels, 0, m_width * m_height * sizeof(T));
}

template<class T> ImageT<T>::~ImageT()
{
  delete[] m_pixels;
  delete[] m_matrix;
}

template<class T> void ImageT<T>::printToConsole(const std::string& description) const
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

      std::cout << (unsigned long long) m_matrix[y][x] << " ";
    }

    std::cout << std::endl;
  }
}

template<class T> unsigned char ImageT<T>::sizeOfOnePixelInBytes() const
{
  return sizeof(T);
}

template<class T> T ImageT<T>::getMaximumValue() const
{
  return std::numeric_limits<T>::max();
}

template<class T> void ImageT<T>::setIncreasingPixelValues()
{
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    m_pixels[i] = i;
  }
}

// list of supported types
template class ImageT<bool>;
template class ImageT<unsigned char>;
template class ImageT<unsigned short>;
template class ImageT<unsigned int>;
template class ImageT<unsigned long>;
template class ImageT<unsigned long long>;
