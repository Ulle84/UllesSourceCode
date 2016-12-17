// see http://doc.qt.io/qt-4.8/qt-itemviews-simpletreemodel-example.html

#include <QString>
#include <QDebug>

#include "TreeModel.h"
#include "ToDoItem.h"


TreeModel::TreeModel(QObject *parent)
  : QAbstractItemModel(parent)
{
  rootItem = new TreeItem(new ToDoItem());
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

Qt::DropActions TreeModel::supportedDropActions() const
{
  // TODO copy?
 return  Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
  /*if (!index.isValid())
  {
    return 0;
  }

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;*/

  Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

       if (index.isValid())
           return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
       else
           return Qt::ItemIsDropEnabled | defaultFlags;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (role == Qt::DisplayRole)
  {
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(index.column());
  }
  else
  {
    return QVariant();
  }
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    QStringList nameOfAttributes = ToDoItem::nameOfAttributes();
    if (section < nameOfAttributes.length())
    {
      return nameOfAttributes.at(section);
    }
    else
    {
      return QVariant();
    }
  }

  return QVariant();
}

void TreeModel::setupModelData(TreeItem *parent)
{
  TreeItem* a = new TreeItem(new ToDoItem("alpha"), parent);
  TreeItem* a1 = new TreeItem(new ToDoItem("alpha1"), a);
  TreeItem* a2 = new TreeItem(new ToDoItem("alpha2"), a);
  TreeItem* a3 = new TreeItem(new ToDoItem("alpha3"), a);

  TreeItem* b = new TreeItem(new ToDoItem("beta"), parent);
  TreeItem* b1 = new TreeItem(new ToDoItem("beta1"), b);
  TreeItem* b2 = new TreeItem(new ToDoItem("beta2"), b);
  TreeItem* b3 = new TreeItem(new ToDoItem("beta3"), b);
}
