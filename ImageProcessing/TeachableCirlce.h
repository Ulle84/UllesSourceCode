#ifndef TEACHABLECIRLCE_H
#define TEACHABLECIRLCE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPen>
#include <QPoint>

#include "Teachable.h"

class TeachableCirlce : public Teachable
{
public:
  TeachableCirlce(QGraphicsEllipseItem* ellipseItem, QGraphicsScene* scene, QPen* pen);

  // Interface Techable
  void setTeachingPointsVisible(bool visible);
  QGraphicsItem* getGraphicsItem();
  void positionChanged(QGraphicsEllipseItem* item, const QPointF& position);
  void update();
  bool hasTeachingPoint(QGraphicsEllipseItem* item);
  QGraphicsEllipseItem* defaultTeachingPoint();

private:
  QPointF pointOnCircle();

  QGraphicsEllipseItem* m_ellipseItem;
  QGraphicsScene* m_scene;
  QPen* m_pen;

  QGraphicsEllipseItem* m_center;
  QGraphicsEllipseItem* m_pointOnCircle;

  QPointF m_teachedPointOnCircle;
};

#endif // TEACHABLECIRLCE_H
