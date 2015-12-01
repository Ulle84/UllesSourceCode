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

  ImageDisplay* imageDisplay = new ImageDisplay(this);
  setCentralWidget(imageDisplay);

  const unsigned int size = 512;
  m_image = new Image(size, size); // width % 4 needs to be zero!
  //m_image->setIncreasingPixelValues();
  //m_image->setRandomPixelValues();

  for (unsigned int i = (size / 2) - 1; i > 0; i--)
  {
    m_image->drawCircle(Circle(Point(size / 2, size / 2), i), i * (512 / size), true);
  }

  FilterMask filterMask(3, 3);

  filterMask.m_matrix[0][0] = -1;
  filterMask.m_matrix[0][1] = -1;
  filterMask.m_matrix[0][2] = -1;

  filterMask.m_matrix[2][0] =  1;
  filterMask.m_matrix[2][1] =  1;
  filterMask.m_matrix[2][2] =  1;

  /*for (unsigned int y = 0; y < filterMask.m_height; y++)
  {
    for (unsigned int x = 0; x < filterMask.m_width; x++)
    {
      filterMask.m_matrix[y][x] = 10;
    }
  }*/

  //m_image->filterWithMask(filterMask);

  Image* polarTransformed = m_image->doPolarTransformation(Circle(Point(size / 2, size / 2), (size / 2) - 1));
  imageDisplay->setImage(polarTransformed);

  //imageDisplay->setImage(m_image);


  // freeman test
  /*QList<unsigned char> directions;

  for (unsigned char i = 0; i < 8; i++)
  {
    directions.append(i);
  }

  FreemanCode freemanCode;
  freemanCode.setStartPoint(Point(10, 10));
  freemanCode.setDirections(directions);

  Image* freemanTest = new Image(20, 20);
  freemanTest->drawFreemanCode(freemanCode);
  imageDisplay->setImage(freemanTest);*/

  // polyline test
  /*QList<Point> points;

  points.append(Point(0, 0));
  points.append(Point(10, 0));
  points.append(Point(10, 10));
  points.append(Point(0, 0));
  points.append(Point(0, 10));
  points.append(Point(19, 19));

  PolyLine polyLine;
  polyLine.setPoints(points);

  Image* polyLineTest = new Image(20, 20);
  polyLineTest->drawPolyLine(polyLine);
  polyLineTest->invert();
  imageDisplay->setImage(polyLineTest);*/

  // histogram test
  /*Image* histogramTest = new Image(512, 100);
  histogramTest->setRandomPixelValues();

  Histogram histogram = histogramTest->getHistogram();
  histogramTest->drawHistogram(histogram);

  imageDisplay->setImage(histogramTest);*/

  // LookUpTable test
  /*LookUpTable lookUpTable;

  Image* lookUpTableTest = new Image(512, 100);
  lookUpTableTest->setIncreasingPixelValues();
  lookUpTableTest->applyLookUpTable(lookUpTable);
  imageDisplay->setImage(lookUpTableTest);*/

  // Matrix-Test
  Matrix<unsigned char> matrix;
  matrix.test();

  qDebug() << "width" << matrix.getWidth();
  qDebug() << "height" << matrix.getHeight();
  qDebug() << "depth" << matrix.getDepth();

}

MainWindow::~MainWindow()
{
  delete ui;
}
