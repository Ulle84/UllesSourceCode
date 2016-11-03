#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "AutoHotKeyHelper.h"

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
  void on_pushButtonSelectFile_clicked();
  void on_pushButtonAppendToFile_clicked();

private:
  Ui::MainWindow *ui;
  QSettings* m_settings;
  AutoHotKeyHelper m_autoHotKeyHelper;
};

#endif // MAINWINDOW_H
