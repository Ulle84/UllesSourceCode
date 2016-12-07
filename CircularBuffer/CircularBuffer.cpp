#include <vector>

#include <QDebug>

#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int numberOfElements)
{
  std::vector<CircularBufferElement*> pointers;

  for (int i = 0; i < numberOfElements; i++)
  {
    m_elements.push_back(CircularBufferElement(i));
    pointers.push_back(&m_elements.back());

    if (i == 0)
    {
      m_currentReadElement = &m_elements.back();
    }
  }

  for (int i = 0; i < numberOfElements; i++)
  {
    pointers[i]->setNext(pointers[(i + 1) % numberOfElements]);
  }
}

void CircularBuffer::readFromBuffer(int numberOfElements)
{
  for (int i = 0; i < numberOfElements; ++i)
  {
    qDebug() << m_currentReadElement->value();
    m_currentReadElement = m_currentReadElement->next();
  }
}
