#include <qmath.h>

#include "Converter.h"

#include "TeachableCirlce.h"

TeachableCirlce::TeachableCirlce(QGraphicsEllipseItem *ellipseItem, QGraphicsScene *scene, QPen *pen) :
  m_ellipseItem(ellipseItem),
  m_scene(scene),
  m_pen(pen)
{
  m_center = scene->addEllipse(Converter::toQRectF(ellipseItem->rect().center()), *m_pen);
  m_pointOnCircle = scene->addEllipse(Converter::toQRectF(pointOnCircle()), *m_pen);
}

void TeachableCirlce::setTeachingPointsVisible(bool visible)
{
  m_center->setVisible(visible);
  m_pointOnCircle->setVisible(visible);
}

QGraphicsItem *TeachableCirlce::getGraphicsItem()
{
  return m_ellipseItem;
}

void TeachableCirlce::positionChanged(QGraphicsEllipseItem *item, const QPointF &position)
{
  QRectF rect = m_ellipseItem->rect();

  if (item == m_center)
  {
    QPointF delta = position - rect.center();
    m_teachedPointOnCircle += delta;

    rect.moveCenter(position);
  }
  else if (item == m_pointOnCircle)
  {
    m_teachedPointOnCircle = position;

    QPointF center = rect.center();

    QPointF delta = position - center;

    double r = sqrt(delta.x() * delta.x() + delta.y() * delta.y());

    QPointF p1(center.x() - r, center.y() - r);
    QPointF p2(center.x() + r, center.y() + r);
    rect = QRectF(p1, p2);
  }

  m_ellipseItem->setRect(rect);
  update();
}

void TeachableCirlce::update()
{
  m_center->setRect(Converter::toQRectF(m_ellipseItem->rect().center()));
  m_pointOnCircle->setRect(Converter::toQRectF(m_teachedPointOnCircle));
}

bool TeachableCirlce::hasTeachingPoint(QGraphicsEllipseItem *item)
{
  return item == m_center || item == m_pointOnCircle;
}

QGraphicsEllipseItem *TeachableCirlce::defaultTeachingPoint()
{
  return m_pointOnCircle;
}

QPointF TeachableCirlce::pointOnCircle()
{
  return QPoint(m_ellipseItem->rect().right(), m_ellipseItem->rect().center().y());
}
