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

  m_imageDisplay = new ImageDisplay(this);
  setCentralWidget(m_imageDisplay);

  imageTest();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_actionOpenImage_triggered()
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

  image->setSingleLayer(qImage.bits(), layerIndices);
  image->mirrorOnVerticalAxis();
  m_imageDisplay->setImage(image);
}

void MainWindow::imageTest()
{
  Image* image = new Image(256, 256);
  image->setAllValues(120);

  std::vector<unsigned long long> histogram = image->getHistogram();
  Image* image2 = new Image(256, 256);
  image2->setHistogram(histogram);

  m_imageDisplay->setImage(image2);
}

void MainWindow::doPolarTransformationTest()
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
