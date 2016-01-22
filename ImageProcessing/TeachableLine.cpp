#include <QDebug>

#include "Converter.h"
#include "TeachableLine.h"

TeachableLine::TeachableLine(QGraphicsLineItem *lineItem, QGraphicsScene* scene, QPen* pen) :
  m_lineItem(lineItem),
  m_scene(scene),
  m_pen(pen)
{
  m_startPoint = scene->addEllipse(Converter::toQRectF(lineItem->line().p1()), *m_pen);
  m_endPoint = scene->addEllipse(Converter::toQRectF(lineItem->line().p2()), *m_pen);
  m_centerPoint = scene->addEllipse(Converter::toQRectF(center()), *m_pen);
}

void TeachableLine::setTeachingPointsVisible(bool visible)
{
  m_startPoint->setVisible(visible);
  m_endPoint->setVisible(visible);
  m_centerPoint->setVisible(visible);
}

QGraphicsItem *TeachableLine::getGraphicsItem()
{
  return m_lineItem;
}

void TeachableLine::positionChanged(QGraphicsEllipseItem *item, const QPointF& position)
{
  QLineF line = m_lineItem->line();

  if (item == m_startPoint)
  {
    line.setP1(position);
  }
  else if (item == m_endPoint)
  {
    line.setP2(position);
  }
  else if (item == m_centerPoint)
  {
    QPointF delta = position - m_center;
    line.setP1(line.p1() + delta);
    line.setP2(line.p2() + delta);
  }

  m_lineItem->setLine(line);
  update();
}

void TeachableLine::update()
{
  m_center = center();

  m_startPoint->setRect(Converter::toQRectF(m_lineItem->line().p1()));
  m_endPoint->setRect(Converter::toQRectF(m_lineItem->line().p2()));
  m_centerPoint->setRect(Converter::toQRectF(m_center));
}

bool TeachableLine::hasTeachingPoint(QGraphicsEllipseItem *item)
{
  return item == m_startPoint || item == m_endPoint || item == m_centerPoint;
}

QGraphicsEllipseItem *TeachableLine::defaultTeachingPoint()
{
  return m_endPoint;
}

QPointF TeachableLine::center()
{
  QPointF start = m_lineItem->line().p1();
  QPointF end = m_lineItem->line().p2();

  float centerX = start.x() + (end.x() - start.x()) / 2;
  float centerY = start.y() + (end.y() - start.y()) / 2;

  return QPointF(centerX, centerY);
}
