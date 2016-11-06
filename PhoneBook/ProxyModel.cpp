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
  // TODO enums instead of hard-coded numbers
  QString firstName = sourceModel()->data(sourceModel()->index(sourceRow, 0, sourceParent)).toString();
  QString lastName = sourceModel()->data(sourceModel()->index(sourceRow, 1, sourceParent)).toString();
  QString phoneNumber = sourceModel()->data(sourceModel()->index(sourceRow, 2, sourceParent)).toString();
  QString room = sourceModel()->data(sourceModel()->index(sourceRow, 3, sourceParent)).toString();

  bool searchStringContained = false;
  // TODO how can I get the setFilterFixedString() directly (without storing in member)?
  searchStringContained |= firstName.contains(m_searchString, Qt::CaseInsensitive);
  searchStringContained |= lastName.contains(m_searchString, Qt::CaseInsensitive);
  searchStringContained |= phoneNumber.contains(m_searchString, Qt::CaseInsensitive);
  searchStringContained |= room.contains(m_searchString, Qt::CaseInsensitive);

  return searchStringContained;
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
