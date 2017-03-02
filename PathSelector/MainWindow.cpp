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

  ui->pathSelector1->setPathType(PathSelector::PathType::Directory);
  ui->pathSelector1->setLabelText("directory");
  ui->pathSelector1->setButtonText("select directory");

  ui->pathSelector2->setPathType(PathSelector::PathType::File);
  ui->pathSelector2->setLabelText("file");
  ui->pathSelector2->setButtonText("select file");
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->pathSelector1->clearHistory(0);
    ui->pathSelector2->clearHistory(2);
}
