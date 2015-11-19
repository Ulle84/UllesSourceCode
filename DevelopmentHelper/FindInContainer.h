#ifndef FINDINCONTAINER_H
#define FINDINCONTAINER_H

#include <QWidget>

namespace Ui {
class FindInContainer;
}

class FindInContainer : public QWidget
{
  Q_OBJECT

public:
  explicit FindInContainer(QWidget *parent = 0);
  ~FindInContainer();

private slots:
  void on_lineEditContainer_returnPressed();
  void on_lineEditElement_returnPressed();
  void on_lineEditIterator_returnPressed();
  void on_checkBoxCreateElseBranch_stateChanged(int arg1);

private:
  void createCode();

  Ui::FindInContainer *ui;
};

#endif // FINDINCONTAINER_H
