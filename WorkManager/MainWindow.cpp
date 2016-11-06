#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "TreeModel.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  TreeModel* m_treeModel = new TreeModel();
  ui->treeView->setModel(m_treeModel);
}

MainWindow::~MainWindow()
{
  delete m_treeModel;
  delete ui;
}
