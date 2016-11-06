#include <QDebug>
#include <QSortFilterProxyModel>

#include "MainWindow.h"
#include "PhoneBook.h"
#include "ProxyModel.h"
#include "ui_MainWindow.h"

#include <QMap>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_phoneBook = new PhoneBook(this);

  m_proxyModel = new ProxyModel(this);

  m_proxyModel->setSourceModel(m_phoneBook);

  ui->tableView->setModel(m_proxyModel);
  ui->tableView->setSortingEnabled(true);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString& text)
{
  m_proxyModel->setSearchString(text);
}
