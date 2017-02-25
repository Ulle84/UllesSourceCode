#ifndef GRIDLAYOUTER_H
#define GRIDLAYOUTER_H

#include <QWidget>

namespace Ui {
class GridLayouter;
}

class GridLayouter : public QWidget
{
  Q_OBJECT

public:
  explicit GridLayouter(QWidget *parent = 0);
  ~GridLayouter();

private:
  void rearrangeInGrid();

  Ui::GridLayouter *ui;
};

#endif // GRIDLAYOUTER_H
