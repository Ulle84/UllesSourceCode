#include <QDebug>
#include <QSettings>
#include <QAction>

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
  connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onTreeViewSelectionChanged);

  ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->treeView->setDragEnabled(true);
  ui->treeView->setAcceptDrops(true);
  ui->treeView->setDropIndicatorShown(true);

  m_actionNew = new QAction(tr("add new item"), this);
  //m_actionNew->setShortcut(QKeySequence::New, QKeySequence::Open);
  //m_actionNew->setShortcut(Qt::Key_Control + Qt::Key_N);
  m_actionNew->setShortcut(QString("Strg+N"));
  connect(m_actionNew, &QAction::triggered, this, &MainWindow::addNewItem);
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
  if (!deselected.isEmpty())
  {
    QModelIndex deselectedIndex = m_proxyModel->mapSelectionToSource(deselected).indexes().first();

    TreeItem *item = static_cast<TreeItem*>(deselectedIndex.internalPointer());
    item->toDoItem()->setDescription(ui->plainTextEdit->toPlainText());
  }

  if (!selected.isEmpty())
  {
    QModelIndex selectedIndex = m_proxyModel->mapSelectionToSource(selected).indexes().first();

    TreeItem *item = static_cast<TreeItem*>(selectedIndex.internalPointer());
    ui->plainTextEdit->setPlainText(item->toDoItem()->description());
  }
}

void MainWindow::addNewItem()
{
  qDebug() << "add new item";
}
