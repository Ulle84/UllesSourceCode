#ifndef CIRCULARBUFFERELEMENT_H
#define CIRCULARBUFFERELEMENT_H


class CircularBufferElement
{
public:
  CircularBufferElement();
  CircularBufferElement(double value);

  void setValue(double value);
  double value() const;

  void setNext(CircularBufferElement* next);
  CircularBufferElement* next() const;

private:
  double m_value;
  CircularBufferElement* m_next;
};

#endif // CIRCULARBUFFERELEMENT_H
