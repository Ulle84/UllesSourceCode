#include <QFile>
#include <QDebug>
#include <QJsonDocument>

#include "TreeModel.h"
#include "ProxyModel.h"

#include "TreeEdit.h"
#include "ui_TreeEdit.h"

TreeEdit::TreeEdit(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TreeEdit)
{
  ui->setupUi(this);

  m_treeModel = new TreeModel(this);
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

  ui->treeView->selectionModel()->setCurrentIndex(m_proxyModel->index(index.row()+1, 0, index.parent()), QItemSelectionModel::ClearAndSelect);

  return true;
}

bool TreeEdit::addChildNode()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  if (indentation(index) >= m_maxIndentation)
  {
    return false;
  }

  if (!m_proxyModel->insertRow(0, index))
    return false;

  ui->treeView->selectionModel()->setCurrentIndex(m_proxyModel->index(0, 0, index), QItemSelectionModel::ClearAndSelect);

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



bool TreeEdit::removeNode()
{
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();

  return m_proxyModel->removeRow(index.row(), index.parent());

  //updateActions();
}

bool TreeEdit::insertColumn()
{
  int column = ui->treeView->selectionModel()->currentIndex().column();

  // Insert a column in the parent item.
  bool changed = m_proxyModel->insertColumn(column + 1);
  if (changed)
      m_proxyModel->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);


  return changed;
}

bool TreeEdit::removeColumn()
{
  int column = ui->treeView->selectionModel()->currentIndex().column();

  // Insert columns in each child of the parent item.
  bool changed = m_proxyModel->removeColumn(column);



  return changed;
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
    qDebug() << "moving right not possible - max indentation level of" << m_maxIndentation << "reached";
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

void TreeEdit::on_pushButton_clicked()
{
  QJsonDocument jsonDocument(m_treeModel->toJson());
  ui->plainTextEdit->setPlainText(jsonDocument.toJson());
}

void TreeEdit::on_pushButton_2_clicked()
{
  m_treeModel->writeFile();
}

void TreeEdit::on_pushButton_3_clicked()
{
  insertColumn();
}

void TreeEdit::on_pushButton_4_clicked()
{
  removeColumn();
}
