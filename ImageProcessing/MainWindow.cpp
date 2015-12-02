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
  filterMaskTest();
  matrixTest();
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

  Image* freemanTest = new Image(20, 20);
  freemanTest->drawFreemanCode(freemanCode);
  m_imageDisplay->setImage(freemanTest);
}

void MainWindow::polarTransformationTest()
{
  for (unsigned int i = (m_size / 2) - 1; i > 0; i--)
  {
    m_image->drawCircle(Circle(Point(m_size / 2, m_size / 2), i), i * (512 / m_size), true);
  }

  Image* polarTransformed = m_image->doPolarTransformation(Circle(Point(m_size / 2, m_size / 2), (m_size / 2) - 1));
  m_imageDisplay->setImage(polarTransformed);
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
  polyLineTest->drawPolyLine(polyLine);
  polyLineTest->invert();
  m_imageDisplay->setImage(polyLineTest);
}

void MainWindow::histogramTest()
{
  Image* histogramTest = new Image(512, 100);
  histogramTest->setRandomPixelValues();

  Histogram histogram = histogramTest->getHistogram();
  histogramTest->drawHistogram(histogram);

  m_imageDisplay->setImage(histogramTest);
}

void MainWindow::lookUpTableTest()
{
  LookUpTable lookUpTable;

  Image* lookUpTableTest = new Image(512, 100);
  lookUpTableTest->setIncreasingPixelValues();
  lookUpTableTest->applyLookUpTable(lookUpTable);

  m_imageDisplay->setImage(lookUpTableTest);
}

void MainWindow::matrixTest()
{
  Matrix<unsigned char>* matrix = new Matrix<unsigned char>(8, 8, 2);
  matrix->setValue(1, 0, 0);
  matrix->setValue(2, 0, 1);
  matrix->spread();
  //matrix->setRandomValues();
  //matrix->binarize(128);
  std::cout << "minimum: " << (int)matrix->getMinimum() << std::endl;
  std::cout << "maximum: " << (int)matrix->getMaximum() << std::endl;

  m_imageDisplay->setMatrix(matrix);
}

void MainWindow::filterMaskTest()
{
  /*FilterMask filterMask(3, 3);

  filterMask.m_matrix[0][0] = -1;
  filterMask.m_matrix[0][1] = -1;
  filterMask.m_matrix[0][2] = -1;

  filterMask.m_matrix[2][0] =  1;
  filterMask.m_matrix[2][1] =  1;
  filterMask.m_matrix[2][2] =  1;*/

  FilterMask filterMask(1, 3);

  filterMask.m_matrix[0][0] = -1;
  filterMask.m_matrix[2][0] =  1;

  m_image->drawRectangle(Rectangle(Point(10, 10), 30, 40), 128);

  m_image->filterWithMask(filterMask);

  m_imageDisplay->setImage(m_image);
}
