#include <QDebug>
#include <QPainter>

#include "RectangleRotated.h"

RectangleRotated::RectangleRotated()
{
}

RectangleRotated::~RectangleRotated()
{
}

QRectF RectangleRotated::boundingRect() const
{
  return m_rectangle;
}

void RectangleRotated::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->drawRect(m_rectangle);
}

RectRotated RectangleRotated::rectangle()
{
  return m_rectangle;
}

void RectangleRotated::setRectangle(const RectRotated &rectRotated)
{
  prepareGeometryChange();
  m_rectangle = rectRotated;
  // TODO update?
}
