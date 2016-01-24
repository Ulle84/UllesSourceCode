#include <iostream>
#include <math.h>

#include "MathHelper.h"

double MathHelper::deg(double angleInRad)
{
  return angleInRad * 180.0 / PI;
}

double MathHelper::rad(double angleInDeg)
{
  return angleInDeg * PI / 180.0;
}

Point MathHelper::calcEndPoint(const Point &startPoint, float angle, float length)
{
  Point endPoint;

  endPoint.m_x = startPoint.m_x + length * cos(rad(angle));
  endPoint.m_y = startPoint.m_y + length * sin(rad(angle));

  //std::cout << "y: " << endPoint.m_y << " x: " << endPoint.m_x << " length: " << length << " angle: " << angle << std::endl;

  return endPoint;
}

void MathHelper::calcAngleAndLength(const Point &startPoint, const Point &endPoint, float &angle, float &length)
{
  short x = endPoint.m_x - startPoint.m_x;
  short y = endPoint.m_y - startPoint.m_y;

  length = sqrt(x * x + y * y);
  angle = deg(atan2(y, x));

  //std::cout << "y: " << endPoint.m_y << " x: " << endPoint.m_x << " length: " << length << " angle: " << angle << std::endl;
}

bool MathHelper::isBetween(float min, float value, float max)
{
  if (value < min)
  {
    return false;
  }
  if (value > max)
  {
    return false;
  }
  return true;
}
