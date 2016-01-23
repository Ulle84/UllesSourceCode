#ifndef RECTROTATED_H
#define RECTROTATED_H

#include <QRectF>

class RectRotated : public QRectF
{
public:
  RectRotated();

  qreal angle();
  void setAngle(qreal angle);

private:
  qreal m_angle;
};

#endif // RECTROTATED_H
