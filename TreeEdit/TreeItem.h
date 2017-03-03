#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QVector>
#include <QByteArray>
#include <QJsonObject>

class TreeItem
{
public:
  explicit TreeItem(const QVector<QVariant> &data, TreeItem *parent = 0);
  ~TreeItem();

  QJsonObject toJson();
  void fromJson(const QJsonObject& json);

  TreeItem *child(int number);
  int childCount() const;
  int columnCount() const;
  QVariant data(int column) const;
  bool insertChildren(int position, int count, int columns);
  bool insertColumns(int position, int columns);
  TreeItem *parent();
  bool removeChildren(int position, int count);
  TreeItem* takeChild(int position);
  bool removeColumns(int position, int columns);
  int childNumber() const;
  bool setData(int column, const QVariant &value);
  void appendChild(TreeItem* child);
  bool insertChild(int position, TreeItem* child);

  bool stringContained(const QString& searchString, Qt::CaseSensitivity caseSensitivity = Qt::CaseInsensitive);
  bool moveChild(int currentPosition, int newPosition);

private:
  QList<TreeItem*> m_childItems;
  QVector<QVariant> m_itemData;
  TreeItem* m_parentItem;
};

#endif
