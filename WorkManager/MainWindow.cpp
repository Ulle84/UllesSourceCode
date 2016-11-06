#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "TreeModel.h"
#include "ProxyModel.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_treeModel = new TreeModel(this);
  m_proxyModel = new ProxyModel(this);

  m_proxyModel->setSourceModel(m_treeModel);

  ui->treeView->setModel(m_proxyModel);
  ui->treeView->expandAll();
}

MainWindow::~MainWindow()
{
  delete m_treeModel;
  delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString& searchString)
{
  m_proxyModel->setSearchString(searchString);
}
