#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Image.h"
#include "ImageT.h"
#include "ImageDisplay.h"

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


  // template test
  /*ImageT<unsigned short> imageT(1, 65537);
  imageT.setIncreasingPixelValues();
  imageT.printToConsole("imageT");
  std::cout << "size of one pixel in bytes: " << (int) imageT.sizeOfOnePixelInBytes() << std::endl;
  std::cout << "max possible value: " << (unsigned long long) imageT.getMaximumValue() << std::endl;*/
}

MainWindow::~MainWindow()
{
  delete ui;
}
