#ifndef GEOMETRYCODEGENERATOR_H
#define GEOMETRYCODEGENERATOR_H

#include <QLineF>
#include <QPointF>
#include <QRectF>
#include <QString>

class GeometryCodeGenerator
{
public:
  GeometryCodeGenerator();

  static QString generate(const QPointF& point);
  static QString generate(const QLineF& line);
  static QString generate(const QRectF& rect);

};

#endif // GEOMETRYCODEGENERATOR_H
