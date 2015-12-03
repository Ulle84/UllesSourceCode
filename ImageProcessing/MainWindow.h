#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Image;
class ImageDisplay;

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
  void on_actionOpenImage_triggered();

private:
  void freemanTest();
  void polyLineTest();
  void matrixTest();
  void colorDisplayTest();

  Ui::MainWindow *ui;
  Image* m_image;
  ImageDisplay* m_imageDisplay;
  int m_size;
};

#endif // MAINWINDOW_H
