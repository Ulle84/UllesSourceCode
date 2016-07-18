#include <QDebug>

#include "Observer.h"

Observer::Observer(const QString& id) :
  m_id(id)
{

}

Observer::~Observer()
{

}

void Observer::notify()
{
  qDebug() << "Observer::notify id: " << m_id;
}
