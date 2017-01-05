#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Converter.h"

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
  void on_plainTextEditInput_textChanged();

private:
  Ui::MainWindow *ui;

  QSettings* m_settings;
  Converter m_converter;
};

#endif // MAINWINDOW_H
