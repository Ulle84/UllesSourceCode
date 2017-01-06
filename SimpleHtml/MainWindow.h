#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Converter.h"

class QSettings;

class Highlighter;

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
  void on_textEditInput_textChanged();

private:
  Ui::MainWindow *ui;

  QSettings* m_settings;
  Converter m_converter;
  Highlighter* m_highlighter;
};

#endif // MAINWINDOW_H
