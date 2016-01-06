#include <QDebug>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "ImageDisplay.h"
#include "Matrix.h"
#include "Image.h"
#include "FilterGenerator.h"
#include "StructuringElementGenerator.h"
#include "Line.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "ImageProcessing", this);

  if (m_settings->contains("lastSelectedFile"))
  {
    m_lastSelectedFile = m_settings->value("lastSelectedFile").toString();
  }

  m_imageDisplay = new ImageDisplay(this);
  setCentralWidget(m_imageDisplay);

  //polyLineTest();
  //edgeDetectionTest();
  //lineDirectionTest();
  //statisticsTest();
  rotatedRectangleTest();
}

MainWindow::~MainWindow()
{
  m_settings->setValue("lastSelectedFile", m_lastSelectedFile);
  delete ui;
}

void MainWindow::on_actionOpenImage_triggered()
{
  QStringList supportedFileFormats;
  supportedFileFormats << "*.bmp" << "*.gif" << "*.jpg" << "*.jpeg" << "*.png" << "*.pbm" << "*.pgm" << "*.ppm" << "*.tif" << "*.tiff" << "*.xbm" << "*.xpm";

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), m_lastSelectedFile, tr("Images (%1)").arg(supportedFileFormats.join(" ")));

  if (fileName.isEmpty())
  {
    return;
  }

  m_lastSelectedFile = fileName;

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

  image->setSingleLayer(qImage.bits(), layerIndices);

  StructuringElement structuringElement = StructuringElementGenerator::circle(7);

  QElapsedTimer timer;
  timer.start();

  image->filterMedian(&structuringElement);

  qDebug() << "The median filter took" << timer.elapsed() << "milliseconds";



  m_imageDisplay->setImage(image);
}

void MainWindow::imageTest()
{
  StructuringElement se = StructuringElementGenerator::circle(20);

  unsigned int width = 30000;//65535;
  unsigned int height = width;


  unsigned int size = width * height;
  std::cout << size << std::endl;
  std::cout << std::numeric_limits<unsigned int>::max() << std::endl;

  Matrix<unsigned char> image(width, height);

  for (unsigned int i = 0; i <= 6; i++)
  {
    QElapsedTimer timer;
    timer.start();

    image.performanceTestAccessPixels(i);

    qDebug() << "method" << i << "took" << timer.elapsed() << "milliseconds";
  }


}

void MainWindow::histogramTest()
{
  Image* image = new Image(256, 256);
  image->setAllValues(120);

  Image* image2 = new Image(256, 256);
  image2->setHistogram(image->getHistogram(0));

  m_imageDisplay->setImage(image2);
}

void MainWindow::polarTransformationTest()
{
  Point point(100, 100);

  Image* image = new Image(200, 200, 1);

  for (unsigned int i = 90; i > 0; i--)
  {
    image->setCircle(i, Circle(point, i));
  }
  image->spread();

  Image* image2 = new Image(image->doPolarTransformation(Circle(point, 90)));

  m_imageDisplay->setImage(image2);
}

void MainWindow::filterTest()
{
  Rectangle rectangle(Point(2, 2), 8, 8);

  Image* image = new Image(12, 12);
  image->setAllValues(100);

  Filter filter = FilterGenerator::sobelHorizontal();

  image->setRectangle(200, rectangle);
  image->filter(&filter);

  m_imageDisplay->setImage(image);

}

void MainWindow::binomialFilterTest()
{
  Image* image = new Image(12, 12);
  Filter filterGaussian = FilterGenerator::binomial(5, 5);

  Rectangle rectangle(Point(2, 2), 8, 8);

  image->setRectangle(128, rectangle);
  image->filter(&filterGaussian);

  m_imageDisplay->setImage(image);
}

void MainWindow::morphologyTest()
{
  Rectangle rectangle(Point(2, 2), 4, 4);

  Image* image = new Image(12, 12);

  StructuringElement structuringElement = StructuringElementGenerator::neighborhood8();

  //image->setPoint(255, Point(127, 127));
  image->setRectangle(255, rectangle, false);
  image->filterMedian(&structuringElement);
  //image->applyFilter(&filter);

  m_imageDisplay->setImage(image);
}

void MainWindow::polyLineTest()
{
  for (unsigned int i = 0; i < 9; i++)
  {
    StructuringElementGenerator::polyLineFillTest(i, false).printValuesToConsole("unfilled");
    StructuringElementGenerator::polyLineFillTest(i, true).printValuesToConsole("filled");
  }
}

void MainWindow::edgeDetectionTest()
{
  Point p1(5, 5);
  Point p2(20, 20);

  Line line(p1, p2);

  Image* image = new Image(40, 40);
  image->setRectangle(128, Rectangle(Point(9, 9), 20, 20));

  Edges edges = image->findEdges(line, 20, 3);

  m_imageDisplay->setImage(image);
}

void MainWindow::lineDirectionTest()
{
  unsigned int width = 3;

  Point c(width / 2, width / 2);

  for (int x = -135; x <= 180; x += 45)
  {
    Line(c, x, x % 90 == 0 ? 1.0 : 1.41);
  }
}

void MainWindow::statisticsTest()
{
  unsigned int width = 5120;
  unsigned int height = 5120;

  Image* image = new Image(width, height);
  image->setIncreasingValues();

  RunLengthCode runLenghtCode;
  //runLenghtCode.push_back(RunLength(Point(0, 0), 2));

  for (unsigned int y = 0; y < height; y++)
  {
    runLenghtCode.push_back(RunLength(Point(0, y), width));
  }

  //runLenghtCode.push_back(RunLength());

  Statistics<unsigned char> statistics = image->getStatistics(runLenghtCode);

  std::cout << "minimum: " << (int) statistics.minimum << std::endl;
  std::cout << "maximum: " << (int) statistics.maximum << std::endl;
  std::cout << "meanValue: " << statistics.meanValue << std::endl;

  m_imageDisplay->setImage(image);
}

void MainWindow::rotatedRectangleTest()
{
  unsigned int width = 256;
  unsigned int height = 256;

  Image* image = new Image(width, height);

  Rectangle rectangle(Point(0, 0), 30, 20, 1);
  image->setRectangle(255, rectangle, true);

  m_imageDisplay->setImage(image);
}
