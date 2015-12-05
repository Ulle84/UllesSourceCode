#include <QDebug>
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
#include "FilterCreator.h"

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

  imageTest();
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

  Filter filter = FilterCreator::laplacian2();
  image->applyFilter(&filter);


  m_imageDisplay->setImage(image);
}

void MainWindow::imageTest()
{
  binomialFilterTest();
}

void MainWindow::histogramTest()
{
  Image* image = new Image(256, 256);
  image->setAllValues(120);

  Image* image2 = new Image(256, 256);
  image2->setHistogram(image->getHistogram());

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
  Point referencePoint(0, 0);
  unsigned int filterSize = 3;
  Filter* filter = new Filter(filterSize, filterSize);
  filter->setReferencePoint(referencePoint);
  filter->setAllValues(1);
  filter->setPreFactor(1.0 / 9);

  Rectangle rectangle(Point(2, 2), 8, 8);

  Image* image = new Image(12, 12);

  Filter filterMean = FilterCreator::mean(5, 5);
  Filter filterGaussian = FilterCreator::binomial(5, 5);

  image->setRectangle(128, rectangle);
  //image->applyFilter(filter);
  image->applyFilter(&filterGaussian);
  //image->setRectangle(255, rectangle);

  m_imageDisplay->setImage(image);

}

void MainWindow::binomialFilterTest()
{
  Image* image = new Image(12, 12);
  Filter filterGaussian = FilterCreator::binomial(5, 5);

  Rectangle rectangle(Point(2, 2), 8, 8);

  image->setRectangle(128, rectangle);
  image->applyFilter(&filterGaussian);

  m_imageDisplay->setImage(image);
}
