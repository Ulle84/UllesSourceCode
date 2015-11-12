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

  m_image = new Image(512, 400); // width % 4 needs to be zero!
  m_image->markRectangle(Rectangle(Point(10, 10), 200, 100), 255);
  m_image->rotateBy90DegreeCounterClockwise();

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
