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
  m_image->setRandomPixelValues();

  imageDisplay->setImage(m_image);
}

MainWindow::~MainWindow()
{
  delete ui;
}
