#include "TreeItem.h"

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent) :
  m_parentItem(parent),
  m_itemData(data)
{
}

TreeItem::~TreeItem()
{
  qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
  m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
  return m_childItems.value(row);
}

QList<TreeItem *> TreeItem::childItems()
{
  return m_childItems;
}

int TreeItem::childCount() const
{
  return m_childItems.count();
}

int TreeItem::row() const
{
  if (m_parentItem)
  {
    return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
  }

  return 0;
}

int TreeItem::columnCount() const
{
  return m_itemData.count();
}

QVariant TreeItem::data(int column) const
{
  return m_itemData.value(column);
}

TreeItem *TreeItem::parent()
{
  return m_parentItem;
}
