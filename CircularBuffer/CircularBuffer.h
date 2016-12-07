#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <list>

#include "CircularBufferElement.h"

class CircularBuffer
{
public:
  CircularBuffer(int numberOfElements);

  void readFromBuffer(int numberOfElements);

private:
  CircularBufferElement* m_currentReadElement; // m_currentWriteElement?
  std::list<CircularBufferElement> m_elements;
};

#endif // CIRCULARBUFFER_H
