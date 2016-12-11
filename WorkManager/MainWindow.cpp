#include <QDebug>
#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "TreeModel.h"
#include "ProxyModel.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "WorkManager", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("headerState"))
  {
    ui->treeView->header()->restoreState(m_settings->value("headerState").toByteArray());
  }

  m_treeModel = new TreeModel(this);
  m_proxyModel = new ProxyModel(this);

  m_proxyModel->setSourceModel(m_treeModel);

  ui->treeView->setModel(m_proxyModel);
  ui->treeView->expandAll();

  // call this connect after setting the model!
  /*connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onTreeViewSelectionChanged);*/
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("headerState", ui->treeView->header()->saveState());

  delete m_treeModel;
  delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString& searchString)
{
  m_proxyModel->setSearchString(searchString);
}

void MainWindow::onTreeViewSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  return;

  if (deselected.indexes().length() > 0)
  {
    QModelIndex deselectedIndex = m_proxyModel->mapSelectionToSource(deselected).indexes().first();

    if (deselectedIndex.isValid())
    {
      ToDoItem *item = static_cast<ToDoItem*>(deselectedIndex.internalPointer());
      item->setDescription(ui->plainTextEdit->toPlainText());
    }
  }

  if (selected.indexes().length() > 0)
  {
    QModelIndex selectedIndex = m_proxyModel->mapSelectionToSource(selected).indexes().first();

    if (selectedIndex.isValid())
    {
      ToDoItem *item = static_cast<ToDoItem*>(selectedIndex.internalPointer());
      ui->plainTextEdit->setPlainText(item->description());
    }
  }
}
