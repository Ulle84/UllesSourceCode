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
  m_image->setIncreasingPixelValues();
  m_image->setRandomPixelValues();
  m_image->binarize(210);
  m_image->dilate(3);
  //m_image->filterMean(13);

  imageDisplay->setImage(m_image);
}

MainWindow::~MainWindow()
{
  delete ui;
}
