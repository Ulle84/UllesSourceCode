#ifndef CONVERTER_H
#define CONVERTER_H

#include <QPointF>
#include <QRectF>

class Converter
{
public:
  static unsigned int toUInt(float value);
  static unsigned int toUInt(double value);

  static QRectF toQRectF(QPointF point, float radius = 5.0);
};

#endif // CONVERTER_H
