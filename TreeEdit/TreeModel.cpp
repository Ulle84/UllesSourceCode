#include <QtWidgets>

#include "TreeItem.h"
#include "TreeModel.h"

TreeModel::TreeModel(const QStringList &headers, const QString &data, QObject *parent)
  : QAbstractItemModel(parent)
{
  QVector<QVariant> rootData;
  foreach (QString header, headers)
  {
    rootData << header;
  }

  m_rootItem = new TreeItem(rootData);
  setupModelData(data.split(QString("\n")), m_rootItem);
}

TreeModel::~TreeModel()
{
  delete m_rootItem;
}

int TreeModel::columnCount(const QModelIndex & /* parent */) const
{
  return m_rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (role != Qt::DisplayRole && role != Qt::EditRole)
    return QVariant();

  TreeItem *item = getItem(index);

  return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return 0;

  return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
  if (index.isValid()) {
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    if (item)
      return item;
  }
  return m_rootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return m_rootItem->data(section);

  return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (parent.isValid() && parent.column() != 0)
    return QModelIndex();
  TreeItem *parentItem = getItem(parent);

  TreeItem *childItem = parentItem->child(row);
  if (childItem)
    return createIndex(row, column, childItem);
  else
    return QModelIndex();
}

bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
  bool success;

  beginInsertColumns(parent, position, position + columns - 1);
  success = m_rootItem->insertColumns(position, columns);
  endInsertColumns();

  return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
  TreeItem *parentItem = getItem(parent);
  bool success;

  beginInsertRows(parent, position, position + rows - 1);
  success = parentItem->insertChildren(position, rows, m_rootItem->columnCount());
  endInsertRows();

  return success;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
    return QModelIndex();

  TreeItem *childItem = getItem(index);
  TreeItem *parentItem = childItem->parent();

  if (parentItem == m_rootItem)
    return QModelIndex();

  return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
  bool success;

  beginRemoveColumns(parent, position, position + columns - 1);
  success = m_rootItem->removeColumns(position, columns);
  endRemoveColumns();

  if (m_rootItem->columnCount() == 0)
    removeRows(0, rowCount());

  return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
  TreeItem *parentItem = getItem(parent);
  bool success = true;

  beginRemoveRows(parent, position, position + rows - 1);
  success = parentItem->removeChildren(position, rows);
  endRemoveRows();

  return success;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
  TreeItem *parentItem = getItem(parent);

  return parentItem->childCount();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (role != Qt::EditRole)
    return false;

  TreeItem *item = getItem(index);
  bool result = item->setData(index.column(), value);

  if (result)
    emit dataChanged(index, index);

  return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
  if (role != Qt::EditRole || orientation != Qt::Horizontal)
    return false;

  bool result = m_rootItem->setData(section, value);

  if (result)
    emit headerDataChanged(orientation, section, section);

  return result;
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
  QList<TreeItem*> parents;
  QList<int> indentations;
  parents << parent;
  indentations << 0;

  int number = 0;

  while (number < lines.count()) {
    int position = 0;
    while (position < lines[number].length()) {
      if (lines[number].at(position) != ' ')
        break;
      ++position;
    }

    QString lineData = lines[number].mid(position).trimmed();

    if (!lineData.isEmpty()) {
      // Read the column data from the rest of the line.
      QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
      QVector<QVariant> columnData;
      for (int column = 0; column < columnStrings.count(); ++column)
        columnData << columnStrings[column];

      if (position > indentations.last()) {
        // The last child of the current parent is now the new parent
        // unless the current parent has no children.

        if (parents.last()->childCount() > 0) {
          parents << parents.last()->child(parents.last()->childCount()-1);
          indentations << position;
        }
      } else {
        while (position < indentations.last() && parents.count() > 0) {
          parents.pop_back();
          indentations.pop_back();
        }
      }

      // Append a new item to the current parent's list of children.
      TreeItem *parent = parents.last();
      parent->insertChildren(parent->childCount(), 1, m_rootItem->columnCount());
      for (int column = 0; column < columnData.size(); ++column)
        parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
    }

    ++number;
  }
}

bool TreeModel::moveUp(const QModelIndex &index)
{
  return move(index, MoveDirection::Up);
}

bool TreeModel::moveDown(const QModelIndex &index)
{
  return move(index, MoveDirection::Down);
}

bool TreeModel::move(const QModelIndex &index, MoveDirection moveDirection)
{
  int currentPosition = index.row();
  int newPosition = 0;
  TreeItem* treeItem = getItem(index.parent());

  if (moveDirection == MoveDirection::Up)
  {
    if (currentPosition == 0)
      return false;

    newPosition = currentPosition - 1;
  }
  else if (moveDirection == MoveDirection::Down)
  {
    if (currentPosition >= treeItem->childCount() - 1)
      return false;

    newPosition = currentPosition + 2;
  }

  if (!beginMoveRows(index.parent(), currentPosition, currentPosition, index.parent(), newPosition))
    return false;

  treeItem->moveChild(currentPosition, moveDirection == MoveDirection::Down ? newPosition - 1 : newPosition);

  endMoveRows();

  return true;
}
