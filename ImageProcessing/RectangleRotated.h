#ifndef RECTANGLEROTATED_H
#define RECTANGLEROTATED_H

#include <QGraphicsItem>

#include "Rectangle.h"

class RectangleRotated : public QGraphicsItem
{
public:
  RectangleRotated();
  ~RectangleRotated();

  enum { Type = UserType + 1 };
  int type() const {return Type;}

  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QPainterPath shape() const;

  Rectangle rectangle();
  void setRectangle(const Rectangle& rectangle);

private:
  Rectangle m_rectangle;
};

#endif // RECTANGLEROTATED_H
