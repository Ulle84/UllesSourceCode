#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "PathSelector", this);

  if (m_settings->contains("geometry"))
    setGeometry(m_settings->value("geometry").toRect());
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  delete ui;
}
