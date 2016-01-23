#include <QDebug>

#include "TeachablePolyLine.h"
#include "Converter.h"
#include "Line.h"
#include "MathHelper.h"

TeachablePolyLine::TeachablePolyLine(GraphicsPolyLineItem *polyLineItem, QGraphicsScene *scene, QPen *pen) :
  m_polyLineItem(polyLineItem),
  m_scene(scene),
  m_pen(pen),
  m_closed(false)
{
  PolyLine polyLine = m_polyLineItem->polyLine();

  for (auto it = polyLine.begin(); it != polyLine.end(); it++)
  {
    m_edgePoints.append(m_scene->addEllipse(QRectF(), *m_pen));
  }

  m_prepend = scene->addEllipse(QRectF(), *m_pen);
  m_append = scene->addEllipse(QRectF(), *m_pen);
  m_close = scene->addEllipse(QRectF(), *m_pen);

  setTeachingPointsVisible(false);
}

void TeachablePolyLine::setTeachingPointsVisible(bool visible)
{
  PolyLine polyLine = m_polyLineItem->polyLine();

  m_prepend->setVisible(m_closed ? false : visible);
  m_append->setVisible(m_closed ? false : visible);
  m_close->setVisible(m_closed ? false : visible && polyLine.size() > 2);

  for (auto it = m_edgePoints.begin(); it != m_edgePoints.end(); it++)
  {
    (*it)->setVisible(visible);
  }


  if (visible)
  {
    float radius = 5.0;

    /*m_center = center();

    QLineF line = m_lineItem->line();


    float factor = 5.0;

    if (line.length() < factor * radius)
    {
      radius = line.length() / factor;
    }*/



    if (!m_closed)
    {
      auto it1 = polyLine.begin();
      auto it2 = it1++;
      Line line1 = Line(*it1, *it2);

      auto it3 = polyLine.rbegin();
      auto it4 = it3++;
      Line line2 = Line(*it3, *it4);

      Point prepend = MathHelper::calcEndPoint(polyLine.front(), line1.angle(), radius * 2.5);
      Point append = MathHelper::calcEndPoint(polyLine.back(), line2.angle(), radius * 2.5);
      Point close = MathHelper::calcEndPoint(polyLine.back(), line2.angle(), radius * 5);

      m_prepend->setRect(Converter::toQRectF(prepend, radius));
      m_append->setRect(Converter::toQRectF(append, radius));
      m_close->setRect(Converter::toQRectF(close, radius));
    }

    unsigned int counter = 0;
    for (auto it = polyLine.begin(); it != polyLine.end(); it++)
    {
      if (counter < m_edgePoints.size())
      {
        m_edgePoints[counter]->setRect(Converter::toQRectF(*it, radius));
      }
      counter++;
    }
  }
}

bool TeachablePolyLine::hasGraphicsItem(QGraphicsItem *item)
{
  return m_polyLineItem == item;
}

void TeachablePolyLine::positionChanged(QGraphicsEllipseItem *item, const QPointF &position)
{
  PolyLine polyLine = m_polyLineItem->polyLine();

  if (isEdgePoint(item))
  {
    auto itPolyLine = polyLine.begin();
    for (auto it = m_edgePoints.begin(); it != m_edgePoints.end(); it++)
    {
      if (*it == item)
      {
        itPolyLine->setX(position.x());
        itPolyLine->setY(position.y());

        if (m_closed && it == m_edgePoints.begin())
        {
          polyLine.rbegin()->setX(position.x());
          polyLine.rbegin()->setY(position.y());
        }

        break;
      }

      itPolyLine++;

      if (itPolyLine == polyLine.end())
      {
        break;
      }
    }
  }
  else if (item == m_append)
  {
    polyLine.push_back(Converter::toPoint(position));
    m_edgePoints.append(m_append);
    m_append = m_scene->addEllipse(QRectF(), *m_pen);
  }
  else if (item == m_prepend)
  {
    polyLine.push_front(Converter::toPoint(position));
    m_edgePoints.prepend(m_prepend);
    m_prepend = m_scene->addEllipse(QRectF(), *m_pen);
  }
  else if (item == m_close)
  {
    if (!m_closed)
    {
      polyLine.push_back(polyLine.front());
      m_closed = true;
    }
  }

  m_polyLineItem->setPolyLine(polyLine);
}

bool TeachablePolyLine::hasTeachingPoint(QGraphicsEllipseItem *item)
{
  return item == m_append || item == m_prepend || item == m_close || isEdgePoint(item);
}

QGraphicsEllipseItem *TeachablePolyLine::defaultTeachingPoint()
{
  return m_edgePoints.last();
}

bool TeachablePolyLine::isEdgePoint(QGraphicsEllipseItem *item)
{
  for (auto it = m_edgePoints.begin(); it != m_edgePoints.end(); it++)
  {
    if (*it == item)
    {
      return true;
    }
  }
  return false;
}

QPointF TeachablePolyLine::center()
{
  QPointF center;

  PolyLine polyLine = m_polyLineItem->polyLine();

  if (polyLine.size() == 2)
  {
    QPointF start = Converter::toQPointF(polyLine.front());
    QPointF end = Converter::toQPointF(polyLine.back());

    center.setX(start.x() + (end.x() - start.x()) / 2);
    center.setY(start.y() + (end.y() - start.y()) / 2);
  }

  return center;
}
