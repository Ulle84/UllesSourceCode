#ifndef TEACHABLERECTANGLE_H
#define TEACHABLERECTANGLE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPen>
#include <QPoint>

#include "Teachable.h"

class TeachableRectangle : public Teachable
{
public:
  TeachableRectangle(QGraphicsRectItem* rectItem, QGraphicsScene* scene, QPen* pen);

  // Interface Techable
  void setTeachingPointsVisible(bool visible);
  QGraphicsItem* getGraphicsItem();
  void positionChanged(QGraphicsEllipseItem* item, const QPointF& position);
  void update();
  bool hasTeachingPoint(QGraphicsEllipseItem* item);
  QGraphicsEllipseItem* defaultTeachingPoint();

private:
  QPointF center();

  QGraphicsRectItem* m_rectItem;
  QGraphicsScene* m_scene;
  QPen* m_pen;

  QGraphicsEllipseItem* m_topLeft;
  QGraphicsEllipseItem* m_topRight;
  QGraphicsEllipseItem* m_bottomLeft;
  QGraphicsEllipseItem* m_bottomRight;
  QGraphicsEllipseItem* m_center;
};

#endif // TEACHABLERECTANGLE_H
