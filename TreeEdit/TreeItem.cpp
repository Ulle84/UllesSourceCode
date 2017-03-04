#include <QStringList>
#include <QJsonArray>
#include <QDebug>

#include "TreeItem.h"

int TreeItem::counter = 0;

TreeItem::TreeItem(const QJsonObject &json, TreeItem *parent)
{
  counter++;

  m_parentItem = parent;

  if (json.contains("attributes") && json["attributes"].isArray())
  {
    QJsonArray attributes = json["attributes"].toArray();
    m_itemData = attributes.toVariantList();
  }

  if (json.contains("children") && json["children"].isArray())
  {
    QJsonArray children = json["children"].toArray();
    for (auto it : children)
    {
      TreeItem* treeItem = new TreeItem(it.toObject(), this);
      appendChild(treeItem);
    }
  }
}

TreeItem::~TreeItem()
{
  qDeleteAll(m_childItems);
}

QJsonObject TreeItem::toJson()
{
  QJsonObject json;

  json["attributes"] = QJsonArray::fromVariantList(m_itemData);

  if (m_childItems.length() > 0)
  {
    QJsonArray ja;
    for (auto it : m_childItems)
    {
      ja.append(it->toJson());
    }
    json["children"] = ja;
  }

  return json;
}

TreeItem *TreeItem::child(int number)
{
  return m_childItems.value(number);
}

int TreeItem::childCount() const
{
  return m_childItems.count();
}

int TreeItem::childNumber() const
{
  if (m_parentItem)
    return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

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

bool TreeItem::insertChildren(int position, int count, int columns)
{
  if (position < 0 || position > m_childItems.size())
    return false;

  for (int row = 0; row < count; ++row) {
    QJsonArray attributes;
    for (int column = 0; column < columns; ++column) {
      attributes.append(counter);
    }

    QJsonObject object;
    object["attributes"] = attributes;

    TreeItem *item = new TreeItem(object, this);
    m_childItems.insert(position, item);
  }

  return true;
}

bool TreeItem::insertColumns(int position, int columns)
{
  if (position < 0 || position > m_itemData.size())
    return false;

  for (int column = 0; column < columns; ++column)
    m_itemData.insert(position, QVariant());

  foreach (TreeItem *child, m_childItems)
    child->insertColumns(position, columns);

  return true;
}

TreeItem *TreeItem::parent()
{
  return m_parentItem;
}

bool TreeItem::removeChildren(int position, int count)
{
  if (position < 0 || position + count > m_childItems.size())
    return false;

  for (int row = 0; row < count; ++row)
    delete m_childItems.takeAt(position);

  return true;
}

TreeItem *TreeItem::takeChild(int position)
{
  return m_childItems.takeAt(position);
}

bool TreeItem::removeColumns(int position, int columns)
{
  if (position < 0 || position + columns > m_itemData.size())
    return false;

  for (int column = 0; column < columns; ++column)
    m_itemData.removeAt(position);

  foreach (TreeItem *child, m_childItems)
    child->removeColumns(position, columns);

  return true;
}

bool TreeItem::setData(int column, const QVariant &value)
{
  if (column < 0 || column >= m_itemData.size())
  {
    return false;
  }

  m_itemData[column] = value;
  return true;
}

void TreeItem::appendChild(TreeItem *child)
{
  m_childItems.append(child);
}

bool TreeItem::insertChild(int position, TreeItem *child)
{
  if (position < 0 || position > m_childItems.length())
  {
    return false;
  }

  m_childItems.insert(position, child);
}

bool TreeItem::stringContained(const QString &searchString, Qt::CaseSensitivity caseSensitivity)
{
  for (auto it : m_itemData)
  {
    if (it.toString().contains(searchString, caseSensitivity))
    {
      return true;
    }
  }

  for (auto it : m_childItems)
  {
    if (it->stringContained(searchString, caseSensitivity))
    {
      return true;
    }
  }

  return false;
}

bool TreeItem::moveChild(int currentPosition, int newPosition)
{
  if (currentPosition < 0 || currentPosition >= m_childItems.length())
    return false;

  if (newPosition < 0 || newPosition >= m_childItems.length())
    return false;

  m_childItems.move(currentPosition, newPosition);
}
