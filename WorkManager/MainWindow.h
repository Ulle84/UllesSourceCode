#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TreeModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  TreeModel* m_treeModel;
};

#endif // MAINWINDOW_H
