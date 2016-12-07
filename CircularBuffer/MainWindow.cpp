#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "CircularBuffer.h"
#include "RingBuffer.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  /*CircularBuffer circularBuffer(4);
  circularBuffer.readFromBuffer(6);*/

  RingBuffer<double> ringBuffer(4);
  ringBuffer.write(1.0);
  ringBuffer.write(2.0);

  qDebug() << ringBuffer.read();
  qDebug() << ringBuffer.read();

  ringBuffer.write(3.0);
  ringBuffer.write(4.0);
  ringBuffer.write(5.0);



  ringBuffer.printValues();
}

MainWindow::~MainWindow()
{
  delete ui;
}
