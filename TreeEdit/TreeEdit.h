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

  bool moveDown();
  bool moveUp();
  bool moveLeft();
  bool moveRight();

  QByteArray headerState() const;
  void setHeaderState(const QByteArray& headerState);

  void setMaxIndentation(unsigned int maxIndentation);

private slots:
  void on_lineEditSearch_textChanged(const QString &arg1);

private:
  QModelIndex selectedIndex();

  Ui::TreeEdit *ui;

  TreeModel* m_treeModel;
  ProxyModel* m_proxyModel;

  unsigned int m_maxIndentation = std::numeric_limits<unsigned int>::max();
};

#endif
