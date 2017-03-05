#ifndef TREEEDIT_H
#define TREEEDIT_H

#include <QWidget>
#include <QItemSelection>

// TODO store state of collapsed
// TODO activate/deactivate actions depending on selected tree-item
// TODO disable search filter before moving
// TODO provide context menu or key-bindings which only are triggered, if treeEdit has focus

class TreeModel;
class ProxyModel;

namespace Ui
{
  class TreeEdit;
}

class TreeEdit : public QWidget
{
  Q_OBJECT

public:
  explicit TreeEdit(QWidget *parent = 0);
  ~TreeEdit();

  bool addNode();
  bool addChildNode();
  bool removeNode();
  bool insertColumn();
  bool removeColumn();

  bool moveDown();
  bool moveUp();
  bool moveLeft();
  bool moveRight();

  QByteArray headerState() const;
  void setHeaderState(const QByteArray& headerState);

  void setMaxIndentation(unsigned int maxIndentation);
  void setTree(const QJsonObject& tree);
  QJsonObject toJson();

signals:
  void idChanged(int id);

private slots:
  void on_lineEditSearch_textChanged(const QString &searchText);
  void onTreeViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
  void onResetRequired(int id);

private:
  void selectId(int id);
  QModelIndex modelIndex(int id, const QModelIndex& parent);
  void getAllIds(QMap<int, QModelIndex>& ids, QModelIndex parent);
  void setupModel(const QJsonObject& tree);
  QModelIndex selectedIndex();
  int indentation(const QModelIndex& modelIndex);

  Ui::TreeEdit *ui;

  TreeModel* m_treeModel;
  ProxyModel* m_proxyModel;

  unsigned int m_maxIndentation = std::numeric_limits<unsigned int>::max();
};

#endif
