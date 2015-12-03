#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QImage>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "ImageDisplay.h"
#include "Matrix.h"
#include "Image.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_size = 512;

  m_imageDisplay = new ImageDisplay(this);
  setCentralWidget(m_imageDisplay);

  //polarTransformationTest();
  //freemanTest();
  //polyLineTest();
  //histogramTest();
  //lookUpTableTest();
  //filterMaskTest();
  //matrixTest();
  //colorDisplayTest();
  imageTest();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_actionOpenImage_triggered(  )
{
  QStringList supportedFileFormats;
  supportedFileFormats << "*.bmp" << "*.gif" << "*.jpg" << "*.jpeg" << "*.png" << "*.pbm" << "*.pgm" << "*.ppm" << "*.tif" << "*.tiff" << "*.xbm" << "*.xpm";

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images (%1)").arg(supportedFileFormats.join(" ")));

  if (fileName.isEmpty())
  {
    return;
  }

  QImage qImage(fileName);

  if (qImage.isNull())
  {
    QMessageBox mb;
    mb.setText(tr("Image could not be opened."));
    mb.exec();
    return;
  }

  std::vector<unsigned int> layerIndices;

  // TODO create class FormatHelper and use also in class ImageDisplay
  QImage::Format format = qImage.format();
  switch(format)
  {
  case QImage::Format_Indexed8:
    layerIndices.push_back(0);
    break;

  case QImage::Format_ARGB32:
  case QImage::Format_RGB32:
    layerIndices.push_back(2);
    layerIndices.push_back(1);
    layerIndices.push_back(0);
    layerIndices.push_back(3);
    break;
  }

  if (layerIndices.size() == 0)
  {
    QMessageBox mb;
    mb.setText(tr("Image format could not be recognized."));
    mb.exec();
    return;
  }

  Image* image = new Image(qImage.width(), qImage.height(), layerIndices.size());

  image->setFromBuffer(qImage.bits(), layerIndices);
  m_imageDisplay->setImage(image);
}

void MainWindow::freemanTest()
{
  std::list<unsigned char> directions;

  for (unsigned char i = 0; i < 8; i++)
  {
    directions.push_back(i);
  }

  FreemanCode freemanCode;
  freemanCode.setStartPoint(Point(10, 12));
  freemanCode.setDirections(directions);

  Image* freemanTest = new Image(20, 20);
  freemanTest->drawFreemanCode(255, freemanCode);
  m_imageDisplay->setImage(freemanTest);
}

void MainWindow::polyLineTest()
{
  std::list<Point> points;

  points.push_back(Point(0, 0));
  points.push_back(Point(10, 0));
  points.push_back(Point(10, 10));
  points.push_back(Point(0, 0));
  points.push_back(Point(0, 10));
  points.push_back(Point(19, 19));

  PolyLine polyLine;
  polyLine.setPoints(points);

  Image* polyLineTest = new Image(20, 20);
  polyLineTest->drawPolyLine(255, polyLine);
  polyLineTest->invert();
  m_imageDisplay->setImage(polyLineTest);
}

void MainWindow::matrixTest()
{
  unsigned int width = 400;
  unsigned int heigth = width;

  Rectangle rectangle(Point(3, 3), 4, 5);
  Point p1(1, 5);
  Point p2(5, 5);
  Point p3(200, 200);

  Circle circle(p3, 180);



  Image* image = new Image(width, heigth, 2);
  image->drawCircle(1, circle, true);
  //matrix->drawLine(1, p1, p2);
  image->spread();
  //matrix->setRandomValues();
  //matrix->binarize(128);
  std::cout << "minimum: " << (int)image->getMinimum() << std::endl;
  std::cout << "maximum: " << (int)image->getMaximum() << std::endl;

  m_imageDisplay->setImage(image);


  width = 20;
  heigth = 20;
  Matrix<unsigned short>* matrix2 = new Matrix<unsigned short>(width, heigth, 1);
  matrix2->setIncreasingValues();
  matrix2->invert();
  matrix2->printValuesToConsole("double matrix");
}

void MainWindow::colorDisplayTest()
{
  // layerCount: 1 -> grey image
  // layerCount: 3 -> 0 = Red, 1 = Green, 2 = Blue
  // layerCount: 4 -> 0 = Red, 1 = Green, 2 = Blue, 3 = Alpha (0 = transparent, 255 = not transparent)
  Image* image = new Image(16, 16, 4);
  image->setAllValues(255);
  image->drawCircle(128, Circle(Point(6, 6), 5), true, 3);
  //matrix->invert();
  m_imageDisplay->setImage(image);
}

void MainWindow::imageTest()
{
  Image* image = new Image(12, 8);
  m_imageDisplay->setImage(image);
}
