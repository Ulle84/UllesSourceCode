#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "BitArray.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  BitArray<char> test;
  test.printAllBits();
}

MainWindow::~MainWindow()
{
  delete ui;
}
