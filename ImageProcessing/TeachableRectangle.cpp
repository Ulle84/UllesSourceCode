#include "Converter.h"

#include "TeachableRectangle.h"


TeachableRectangle::TeachableRectangle(QGraphicsRectItem *rectItem, QGraphicsScene *scene, QPen *pen) :
  m_rectItem(rectItem),
  m_scene(scene),
  m_pen(pen)
{
  m_topLeft = scene->addEllipse(Converter::toQRectF(rectItem->rect().topLeft()), *m_pen);
  m_topRight = scene->addEllipse(Converter::toQRectF(rectItem->rect().topRight()), *m_pen);
  m_bottomLeft = scene->addEllipse(Converter::toQRectF(rectItem->rect().bottomLeft()), *m_pen);
  m_bottomRight = scene->addEllipse(Converter::toQRectF(rectItem->rect().bottomRight()), *m_pen);
  m_center = scene->addEllipse(Converter::toQRectF(rectItem->rect().center()), *m_pen);
}

void TeachableRectangle::setTeachingPointsVisible(bool visible)
{
  m_topLeft->setVisible(visible);
  m_topRight->setVisible(visible);
  m_bottomLeft->setVisible(visible);
  m_bottomRight->setVisible(visible);
  m_center->setVisible(visible);
}

QGraphicsItem *TeachableRectangle::getGraphicsItem()
{
  return m_rectItem;
}

void TeachableRectangle::positionChanged(QGraphicsEllipseItem *item, const QPointF &position)
{
  QRectF rect = m_rectItem->rect();

  if (item == m_topLeft)
  {
    rect.setTopLeft(position);
  }
  else if (item == m_topRight)
  {
    rect.setTopRight(position);
  }
  else if (item == m_bottomLeft)
  {
    rect.setBottomLeft(position);
  }
  else if (item == m_bottomRight)
  {
    rect.setBottomRight(position);
  }
  else if (item == m_center)
  {
    rect.moveCenter(position);
  }

  m_rectItem->setRect(rect);
  update();
}

void TeachableRectangle::update()
{
  m_topLeft->setRect(Converter::toQRectF(m_rectItem->rect().topLeft()));
  m_topRight->setRect(Converter::toQRectF(m_rectItem->rect().topRight()));
  m_bottomLeft->setRect(Converter::toQRectF(m_rectItem->rect().bottomLeft()));
  m_bottomRight->setRect(Converter::toQRectF(m_rectItem->rect().bottomRight()));
  m_center->setRect(Converter::toQRectF(m_rectItem->rect().center()));
}

bool TeachableRectangle::hasTeachingPoint(QGraphicsEllipseItem *item)
{
  return item == m_topLeft || item == m_topRight || item == m_bottomLeft || item == m_bottomRight || item == m_center;
}

QGraphicsEllipseItem *TeachableRectangle::defaultTeachingPoint()
{
  return m_bottomRight;
}
