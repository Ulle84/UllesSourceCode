#ifndef TREEEDIT_H
#define TREEEDIT_H

#include <QWidget>
#include <QItemSelection>

// TODO move left does not work correctly
// TODO move right does not work correctly
// TODO save to file
// TODO load from file
// TODO store state of collapsed
// TODO activate/deactivate actions depending on selected tree-item
// TODO add new column - ask for column header at creation
// TODO disable search filter before moving

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

private slots:
  void on_lineEditSearch_textChanged(const QString &searchText);
  void onTreeViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
  void onResetRequired(int id);
  void on_pushButton_clicked();

private:
  void selectId(int id);
  //QList<int> allIds(QModelIndex parent);
  void getAllIds(QMap<int, QModelIndex>& ids, QModelIndex parent);
  void setupModel();
  QModelIndex selectedIndex();
  int indentation(const QModelIndex& modelIndex);

  Ui::TreeEdit *ui;

  TreeModel* m_treeModel;
  ProxyModel* m_proxyModel;

  unsigned int m_maxIndentation = std::numeric_limits<unsigned int>::max();
};

#endif
