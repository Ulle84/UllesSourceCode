#include "GeometryCodeGenerator.h"

GeometryCodeGenerator::GeometryCodeGenerator()
{
}

QString GeometryCodeGenerator::generate(const QPointF &point)
{
  return QString("Point point(%1, %2").arg(point.x()).arg(point.y());
}

QString GeometryCodeGenerator::generate(const QLineF &line)
{
  return QString("Line line(%1, %2)").arg(generate(line.p1())).arg(generate(line.p2()));
}

QString GeometryCodeGenerator::generate(const QRectF &rect)
{
  return QString("Rectangle rectangle(%1, %2, %3)").arg(generate(rect.topLeft())).arg(rect.width()).arg(rect.height());
}
