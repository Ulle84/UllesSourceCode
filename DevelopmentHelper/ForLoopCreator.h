#ifndef FORLOOPCREATOR_H
#define FORLOOPCREATOR_H

#include <QWidget>

namespace Ui {
class ForLoopCreator;
}

class ForLoopCreator : public QWidget
{
  Q_OBJECT

public:
  explicit ForLoopCreator(QWidget *parent = 0);
  ~ForLoopCreator();

private slots:
  void on_lineEditForLoopIterator_returnPressed();
  void on_lineEditForLoopEnd_returnPressed();

private:
  void createCode();

  Ui::ForLoopCreator *ui;
};

#endif // FORLOOPCREATOR_H
