#include <QtWidgets>

#include "TreeItem.h"
#include "TreeModel.h"

TreeModel::TreeModel(QObject *parent)
  : QAbstractItemModel(parent)
{
  m_rootItem = new TreeItem(readFile());
}

TreeModel::~TreeModel()
{
  writeFile();
  delete m_rootItem;
}

QJsonObject TreeModel::toJson()
{
  return m_rootItem->toJson();
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


void TreeModel::writeFile()
{
  QFile file(m_fileName);

  if (!file.open(QIODevice::WriteOnly))
  {
    qWarning("Couldn't open save file.");
  }

  QJsonDocument jsonDocument(m_rootItem->toJson());

  file.write(jsonDocument.toJson());
  file.close();
}

QJsonObject TreeModel::readFile()
{
  QFile file(m_fileName);

  if (!file.open(QIODevice::ReadOnly))
  {
    qWarning("Couldn't open save file.");
  }

  QString settings = file.readAll();
  file.close();


  QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
  return sd.object();
}

bool TreeModel::moveUp(const QModelIndex &index)
{
  return move(index, MoveDirection::Up);
}

bool TreeModel::moveDown(const QModelIndex &index)
{
  return move(index, MoveDirection::Down);
}

bool TreeModel::moveRight(const QModelIndex &index)
{
  return move(index, MoveDirection::Right);
}

bool TreeModel::moveLeft(const QModelIndex &index)
{
  return move(index, MoveDirection::Left);
}

bool TreeModel::move(const QModelIndex &modelIndex, MoveDirection moveDirection)
{
  // TODO moveDirection right and left
  // TODO select item after moving around
  // TODO new node and new child node have different selecting behaviour after adding

  int currentPosition = modelIndex.row();
  int newPosition = 0;
  TreeItem* treeItem = getItem(modelIndex.parent());
  QModelIndex destinationParent = modelIndex.parent();

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
  else if (moveDirection == MoveDirection::Right)
  {
    if (currentPosition == 0)
      return false;

    destinationParent = index(modelIndex.row() - 1, modelIndex.column(), destinationParent);
  }
  else if (moveDirection == MoveDirection::Left)
  {
    destinationParent = destinationParent.parent();
    newPosition = 0; // TODO calculate depending on parent row
  }

  if (!beginMoveRows(modelIndex.parent(), currentPosition, currentPosition, destinationParent, newPosition))
    return false;

  if (moveDirection == MoveDirection::Down || moveDirection == MoveDirection::Up)
  {
    treeItem->moveChild(currentPosition, moveDirection == MoveDirection::Down ? newPosition - 1 : newPosition);
  }
  else if (moveDirection == MoveDirection::Right)
  {
    getItem(destinationParent)->appendChild(treeItem->takeChild(currentPosition));
  }
  else if (moveDirection == MoveDirection::Left)
  {
    getItem(destinationParent)->insertChild(newPosition, treeItem->takeChild(currentPosition));
  }

  endMoveRows();

  return true;
}
