#ifndef RECTANGLEROTATED_H
#define RECTANGLEROTATED_H

#include <QGraphicsItem>

#include "RectRotated.h"

class RectangleRotated : public QGraphicsItem
{
public:
  RectangleRotated();
  ~RectangleRotated();

  enum { Type = UserType + 1 };
  int type() const {return Type;}

  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  RectRotated rectangle();
  void setRectangle(const RectRotated& rectRotated);

private:
  RectRotated m_rectangle;
};

#endif // RECTANGLEROTATED_H
