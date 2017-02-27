#include <QFile>
#include <QDebug>

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

  if (!m_proxyModel->insertRow(index.row()+1, index.parent()))
    return false;

  //updateActions();

  for (int column = 0; column < m_proxyModel->columnCount(index.parent()); ++column) {
    QModelIndex child = m_proxyModel->index(index.row()+1, column, index.parent());
    m_proxyModel->setData(child, QVariant("[No data]"), Qt::EditRole);
  }

  return true;
}

int TreeEdit::indentation(const QModelIndex& modelIndex)
{
  int indent = 0;
  QModelIndex parent = modelIndex.parent();
  while (parent.isValid())
  {
    indent++;
    parent = parent.parent();
  }

  return indent;
}

bool TreeEdit::addChildNode()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  if (indentation(index) >= m_maxIndentation)
  {
    return false;
  }

  if (m_proxyModel->columnCount(index) == 0) {
    if (!m_proxyModel->insertColumn(0, index))
      return false;
  }

  if (!m_proxyModel->insertRow(0, index))
    return false;

  for (int column = 0; column < m_proxyModel->columnCount(index); ++column) {
    QModelIndex child = m_proxyModel->index(0, column, index);
    m_proxyModel->setData(child, QVariant("[No data]"), Qt::EditRole);
    if (!m_proxyModel->headerData(column, Qt::Horizontal).isValid())
      m_proxyModel->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
  }

  ui->treeView->selectionModel()->setCurrentIndex(m_proxyModel->index(0, 0, index), QItemSelectionModel::ClearAndSelect);
  //updateActions();

  return true;
}

bool TreeEdit::removeNode()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  return m_proxyModel->removeRow(index.row(), index.parent());

  //updateActions();
}

bool TreeEdit::moveDown()
{
  return m_treeModel->moveDown(selectedIndex());
}

bool TreeEdit::moveUp()
{
  return m_treeModel->moveUp(selectedIndex());
}

bool TreeEdit::moveLeft()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  if (indentation(index) <= 0)
  {
    qDebug() << "moving left not possible - already a top level element";
    return false;
  }

  return m_treeModel->moveLeft(selectedIndex());
}

bool TreeEdit::moveRight()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  if (indentation(index) >= m_maxIndentation)
  {
    qDebug() << "moving right not possible because maxIndentation level of" << m_maxIndentation << "is reached";
    return false;
  }

  return m_treeModel->moveRight(selectedIndex());
}

QByteArray TreeEdit::headerState() const
{
  return ui->treeView->header()->saveState();
}

void TreeEdit::setHeaderState(const QByteArray &headerState)
{
  ui->treeView->header()->restoreState(headerState);
}

void TreeEdit::setMaxIndentation(unsigned int maxIndentation)
{
  m_maxIndentation = maxIndentation;
}

void TreeEdit::on_lineEditSearch_textChanged(const QString &searchText)
{
  m_proxyModel->setSearchString(searchText);
}

QModelIndex TreeEdit::selectedIndex()
{
  return m_proxyModel->mapToSource(ui->treeView->selectionModel()->currentIndex());
}
