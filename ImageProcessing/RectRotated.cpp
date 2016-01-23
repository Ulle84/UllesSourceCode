#include "RectRotated.h"

RectRotated::RectRotated()
{
}

qreal RectRotated::angle()
{
  return m_angle;
}

void RectRotated::setAngle(qreal angle)
{
  m_angle = angle;
}
