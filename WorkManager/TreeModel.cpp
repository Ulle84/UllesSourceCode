// see http://doc.qt.io/qt-4.8/qt-itemviews-simpletreemodel-example.html

#include <QString>

#include "TreeModel.h"


TreeModel::TreeModel(QObject *parent)
  : QAbstractItemModel(parent)
{
  QList<QVariant> rootData;
  rootData << "Title";
  rootItem = new TreeItem(rootData);
  setupModelData(rootItem);
}

TreeModel::~TreeModel()
{
  delete rootItem;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
  {
    return QModelIndex();
  }

  TreeItem *parentItem;

  if (!parent.isValid())
  {
    parentItem = rootItem;
  }
  else
  {
    parentItem = static_cast<TreeItem*>(parent.internalPointer());
  }

  TreeItem *childItem = parentItem->child(row);
  if (childItem)
  {
    return createIndex(row, column, childItem);
  }
  else
  {
    return QModelIndex();
  }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
  {
    return QModelIndex();
  }

  TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = childItem->parent();

  if (parentItem == rootItem)
  {
    return QModelIndex();
  }

  return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
  TreeItem *parentItem;
  if (parent.column() > 0)
  {
    return 0;
  }

  if (!parent.isValid())
  {
    parentItem = rootItem;
  }
  else
  {
    parentItem = static_cast<TreeItem*>(parent.internalPointer());
  }

  return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
  {
    return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
  }
  else
  {
    return rootItem->columnCount();
  }
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

  return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
  {
    return 0;
  }

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    return rootItem->data(section);
  }

  return QVariant();
}

void TreeModel::setupModelData(TreeItem *parent)
{
  TreeItem* livingRoom = new TreeItem(QList<QVariant>() << QString("Living Room"), parent);
  parent->appendChild(livingRoom);

  livingRoom->appendChild(new TreeItem(QList<QVariant>() << QString("clean up"), livingRoom));

  TreeItem* kitchen = new TreeItem(QList<QVariant>() << QString("Kitchen"), parent);
  parent->appendChild(kitchen);

  TreeItem* whashTheDishes = new TreeItem(QList<QVariant>() << QString("whash the dishes"), kitchen);
  kitchen->appendChild(whashTheDishes);

  whashTheDishes->appendChild(new TreeItem(QList<QVariant>() << QString("step 1"), whashTheDishes));
  whashTheDishes->appendChild(new TreeItem(QList<QVariant>() << QString("step 2"), whashTheDishes));
  whashTheDishes->appendChild(new TreeItem(QList<QVariant>() << QString("step 3"), whashTheDishes));
}
