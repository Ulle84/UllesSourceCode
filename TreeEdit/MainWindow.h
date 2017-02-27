#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;

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
  void on_actionAddNewNode_triggered();

  void on_actionAddNewChildNode_triggered();

  void on_actionRemoveNode_triggered();

  void on_actionMoveUp_triggered();

  void on_actionMoveDown_triggered();

  void on_actionMoveLeft_triggered();

  void on_actionMoveRight_triggered();

private:
  Ui::MainWindow *ui;
  QSettings* m_settings;
};

#endif
