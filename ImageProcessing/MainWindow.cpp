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

  m_image = new Image(256, 256); // width % 4 needs to be zero!
  m_image->drawCircle(Point(128, 128), 120, 255);

  /*m_image->drawRectangle(Rectangle(Point(10, 10), 200, 100), 255);
  m_image->drawRectangle(Rectangle(Point(15, 15), 3, 3), 0);
  m_image->drawRectangle(Rectangle(Point(6, 6), 3, 3), 255);*/
  //m_image->doClosing(7);
  //m_image->doOpening(7);
  //m_image->rotateBy90DegreeCounterClockwise();

  /*m_image = new Image(8, 4);
  m_image->setIncreasingPixelValues();
  m_image->printToConsole("original");
  m_image->rotateBy90DegreeCounterClockwise();
  m_image->printToConsole("rotatedBy90DegreeCounterClockwise");*/

  imageDisplay->setImage(m_image);
}

MainWindow::~MainWindow()
{
  delete ui;
}
