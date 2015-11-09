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
  m_image->setAllPixelValues(120);

  Point point(1, 2);
  Rectangle rectangle(point, 3, 2);

  m_image->markRectangle(rectangle, 121);
  m_image->spread();

  /*m_image->markLine(1, 127);
  m_image->markLine(2, 255);

  m_image->markColumn(1, 255);*/



  /*m_image->setRandomPixelValues();
  m_image->binarize(210);
  m_image->dilate(3);
  m_image->filterMean(13);*/

  /*m_image->markPoint(Point(3, 3), 255);
  m_image->dilate(5);
  m_image->markPoint(Point(12, 12), 255);*/

  imageDisplay->setImage(m_image);
}

MainWindow::~MainWindow()
{
  delete ui;
}
