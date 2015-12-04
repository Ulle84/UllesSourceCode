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
  void imageTest();
  void doPolarTransformationTest();

  Ui::MainWindow* ui;
  Image* m_image;
  ImageDisplay* m_imageDisplay;
};

#endif // MAINWINDOW_H
