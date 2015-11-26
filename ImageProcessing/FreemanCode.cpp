#include "FreemanCode.h"

FreemanCode::FreemanCode()
{

}

void FreemanCode::setStartPoint(const Point &startPoint)
{
  m_startPoint = startPoint;
}

void FreemanCode::setDirections(const QList<unsigned char> &directions)
{
  m_directions = directions;
}

