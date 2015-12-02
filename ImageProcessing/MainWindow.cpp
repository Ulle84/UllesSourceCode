#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Image.h"
#include "ImageDisplay.h"
#include "Matrix.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_size = 512;

  m_imageDisplay = new ImageDisplay(this);
  setCentralWidget(m_imageDisplay);

  m_image = new Image(m_size, m_size); // width % 4 needs to be zero!

  //polarTransformationTest();
  //freemanTest();
  //polyLineTest();
  //histogramTest();
  //lookUpTableTest();
  //filterMaskTest();
  //matrixTest();
  colorDisplayTest();
}

MainWindow::~MainWindow()
{
  delete ui;
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

  Matrix<unsigned char>* freemanTest = new Matrix<unsigned char>(20, 20);
  freemanTest->drawFreemanCode(255, freemanCode);
  m_imageDisplay->setMatrix(freemanTest);
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

  Matrix<unsigned char>* polyLineTest = new Matrix<unsigned char>(20, 20);
  polyLineTest->drawPolyLine(255, polyLine);
  polyLineTest->invert();
  m_imageDisplay->setMatrix(polyLineTest);
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



  Matrix<unsigned char>* matrix = new Matrix<unsigned char>(width, heigth, 2);
  matrix->drawCircle(1, circle, true);
  //matrix->drawLine(1, p1, p2);
  matrix->spread();
  //matrix->setRandomValues();
  //matrix->binarize(128);
  std::cout << "minimum: " << (int)matrix->getMinimum() << std::endl;
  std::cout << "maximum: " << (int)matrix->getMaximum() << std::endl;

  m_imageDisplay->setMatrix(matrix);


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
  Matrix<unsigned char>* matrix = new Matrix<unsigned char>(12, 12, 3);
  m_imageDisplay->setMatrix(matrix);
}
