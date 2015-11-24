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

  m_image = new Image(16, 16); // width % 4 needs to be zero!
  //m_image->setIncreasingPixelValues();
  //m_image->setRandomPixelValues();
  m_image->drawCircle(Circle(Point(8, 8), 6), 128, true);


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

  m_image->filterWithMask(filterMask);

  imageDisplay->setImage(m_image);
}

MainWindow::~MainWindow()
{
  delete ui;
}
