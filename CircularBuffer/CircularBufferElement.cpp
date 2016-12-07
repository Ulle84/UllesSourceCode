#include "CircularBufferElement.h"

CircularBufferElement::CircularBufferElement()
{

}

CircularBufferElement::CircularBufferElement(double value) :
  m_value(value)
{

}

void CircularBufferElement::setValue(double value)
{
  m_value = value;
}

double CircularBufferElement::value() const
{
  return m_value;
}

void CircularBufferElement::setNext(CircularBufferElement *next)
{
  m_next = next;
}

CircularBufferElement *CircularBufferElement::next() const
{
  return m_next;
}
