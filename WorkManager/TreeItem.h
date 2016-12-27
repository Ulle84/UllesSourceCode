#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

#include "ToDoItem.h"

class TreeItem
{
public:
  TreeItem(ToDoItem* toDoItem, TreeItem *parent = nullptr);
  ~TreeItem();

  void appendChild(TreeItem *child);

  TreeItem* child(int row);
  QList<TreeItem*> childItems();
  int childCount() const;
  int columnCount() const;
  QVariant data(int column) const;
  int row() const;
  TreeItem* parent();

  ToDoItem* toDoItem();

private:
  QList<TreeItem*> m_childItems;
  ToDoItem* m_toDoItem;
  TreeItem* m_parentItem;
};

#endif
