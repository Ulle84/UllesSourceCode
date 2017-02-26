#include <QFile>

#include "TreeModel.h"
#include "ProxyModel.h"

#include "TreeEdit.h"
#include "ui_TreeEdit.h"

TreeEdit::TreeEdit(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TreeEdit)
{
  ui->setupUi(this);

  QStringList headers;
  headers << tr("Title") << tr("Description");

  QFile file("/Users/Ulle/Programmierung/UllesSourceCode/TreeEdit/default.txt");
  file.open(QIODevice::ReadOnly);
  m_treeModel = new TreeModel(headers, file.readAll());
  file.close();



  m_proxyModel = new ProxyModel(this);

  m_proxyModel->setSourceModel(m_treeModel);

  ui->treeView->setModel(m_proxyModel);
  ui->treeView->expandAll();
}

TreeEdit::~TreeEdit()
{
  delete ui;
}

bool TreeEdit::addNode()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();
  QAbstractItemModel *model = ui->treeView->model();

  if (!model->insertRow(index.row()+1, index.parent()))
      return false;

  //updateActions();

  for (int column = 0; column < model->columnCount(index.parent()); ++column) {
      QModelIndex child = model->index(index.row()+1, column, index.parent());
      model->setData(child, QVariant("[No data]"), Qt::EditRole);
  }

  return true;
}

bool TreeEdit::addChildNode()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();
  QAbstractItemModel *model = ui->treeView->model();

  if (model->columnCount(index) == 0) {
      if (!model->insertColumn(0, index))
          return false;
  }

  if (!model->insertRow(0, index))
      return false;

  for (int column = 0; column < model->columnCount(index); ++column) {
      QModelIndex child = model->index(0, column, index);
      model->setData(child, QVariant("[No data]"), Qt::EditRole);
      if (!model->headerData(column, Qt::Horizontal).isValid())
          model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
  }

  ui->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index), QItemSelectionModel::ClearAndSelect);
  //updateActions();

  return true;
}

bool TreeEdit::removeNode()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();
  QAbstractItemModel *model = ui->treeView->model();

  return model->removeRow(index.row(), index.parent());

  //updateActions();
}

QByteArray TreeEdit::headerState() const
{
  return ui->treeView->header()->saveState();
}

void TreeEdit::setHeaderState(const QByteArray &headerState)
{
  ui->treeView->header()->restoreState(headerState);
}

void TreeEdit::on_lineEditSearch_textChanged(const QString &searchText)
{
    m_proxyModel->setSearchString(searchText);
}
