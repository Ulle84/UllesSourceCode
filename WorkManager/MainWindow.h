#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>

class TreeModel;
class ProxyModel;
class QSettings;
class QAction;

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
  void onTreeViewSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
  void addNewItem();

private:
  Ui::MainWindow *ui;
  TreeModel* m_treeModel;
  ProxyModel* m_proxyModel;
  QSettings* m_settings;
  QAction* m_actionNew;
};

#endif // MAINWINDOW_H
