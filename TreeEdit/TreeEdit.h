#ifndef TREEEDIT_H
#define TREEEDIT_H

#include <QWidget>

class TreeModel;
class ProxyModel;

namespace Ui {
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

  QByteArray headerState() const;
  void setHeaderState(const QByteArray& headerState);

private:
  Ui::TreeEdit *ui;

  TreeModel* m_treeModel;
  ProxyModel* m_proxyModel;
};

#endif
