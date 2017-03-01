#include <QSettings>
#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "TreeEdit", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }
  if (m_settings->contains("headerState"))
  {
    ui->treeEdit->setHeaderState(m_settings->value("headerState").toByteArray());
  }

  //ui->treeEdit->setMaxIndentation(2);
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("headerState", ui->treeEdit->headerState());
  delete ui;
}

void MainWindow::on_actionAddNewNode_triggered()
{
  ui->treeEdit->addNode();
}

void MainWindow::on_actionAddNewChildNode_triggered()
{
  ui->treeEdit->addChildNode();
}

void MainWindow::on_actionRemoveNode_triggered()
{
  ui->treeEdit->removeNode();
}

void MainWindow::on_actionMoveUp_triggered()
{
  ui->treeEdit->moveUp();
}

void MainWindow::on_actionMoveDown_triggered()
{
  ui->treeEdit->moveDown();
}

void MainWindow::on_actionMoveLeft_triggered()
{
  ui->treeEdit->moveLeft();
}

void MainWindow::on_actionMoveRight_triggered()
{
  ui->treeEdit->moveRight();
}