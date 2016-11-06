#include <QDateTime>
#include <QDebug>
#include <QModelIndex>

#include "ProxyModel.h"

ProxyModel::ProxyModel(QObject* parent) :
  QSortFilterProxyModel(parent)
{

}

bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
  // look if one of the child nodes contains the search string, return immediatly true, if a match was found

  // TODO get "own" QModelIndex and iterate (recursivly) over all children



  qDebug() << "sourceRow" << sourceRow;

  QString title = sourceModel()->data(sourceModel()->index(sourceRow, 0, sourceParent)).toString();

  qDebug() << "title" << title;

  return title.contains(m_searchString, Qt::CaseInsensitive);
}

void ProxyModel::setSearchString(const QString& searchString)
{
  m_searchString = searchString;
  setFilterFixedString(searchString);
}

bool ProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
  return sourceModel()->data(left).toString() < sourceModel()->data(right).toString();
}
