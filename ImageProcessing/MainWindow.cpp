#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Image.h"
#include "ImageDisplay.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ImageDisplay* imageDisplay = new ImageDisplay(this);
  setCentralWidget(imageDisplay);

  m_image = new Image(16, 16); // width % 4 needs to be zero!

  Circle circle(Point(8, 8), 7);
  m_image->drawCircle(circle, 255, true);

  imageDisplay->setImage(m_image);
}

MainWindow::~MainWindow()
{
  delete ui;
}
