#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class QSettings;

#include "IncludeFinder.h"

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


  void on_pushButtonSelectDirectory_clicked();

  void on_pushButtonSearch_clicked();

private:
  void parseFolder();

  Ui::MainWindow *ui;
  IncludeFinder m_includeFinder;
  QSettings* m_settings;
};

#endif // MAINWINDOW_H
