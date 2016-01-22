#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MyClass.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  MyClass myClass;
  myClass.function();
}

MainWindow::~MainWindow()
{
  delete ui;
}
