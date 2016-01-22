#include <iostream>

#include <QDebug>

#include "Converter.h"


unsigned int Converter::toUInt(float value)
{
  if (value < 0.0)
  {
    return 0;
  }

  unsigned int result = value + 0.5;

  return result;
}

unsigned int Converter::toUInt(double value)
{
  if (value < 0.0)
  {
    return 0;
  }

  unsigned int result = value + 0.5;

  return result;
}

QRectF Converter::toQRectF(QPointF point, float radius)
{
  QPointF offset(radius, radius);
  return QRectF(point - offset, point + offset);
}
