#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TreeModel;
class ProxyModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_lineEdit_textChanged(const QString& searchString);

private:
  Ui::MainWindow *ui;
  TreeModel* m_treeModel;
  ProxyModel* m_proxyModel;
};

#endif // MAINWINDOW_H
