#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Image;

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
  Image* m_image;
};

#endif // MAINWINDOW_H
