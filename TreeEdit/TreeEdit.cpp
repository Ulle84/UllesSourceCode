#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QInputDialog>

#include "TreeModel.h"
#include "ProxyModel.h"
#include "TreeItem.h"

#include "TreeEdit.h"
#include "ui_TreeEdit.h"

TreeEdit::TreeEdit(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TreeEdit)
{
  ui->setupUi(this);

  setupModel();
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
}

bool TreeEdit::insertColumn()
{
  bool inputOk;
  QString columnName = QInputDialog::getText(this, tr("input column name"), tr("column name"), QLineEdit::Normal, QString(), &inputOk);

  if (!inputOk || columnName.isEmpty())
  {
    return false;
  }

  int column = ui->treeView->selectionModel()->currentIndex().column();

  bool changed = m_proxyModel->insertColumn(column + 1);
  if (changed)
    m_proxyModel->setHeaderData(column + 1, Qt::Horizontal, columnName, Qt::EditRole);

  return changed;
}

bool TreeEdit::removeColumn()
{
  int column = ui->treeView->selectionModel()->currentIndex().column();
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

void TreeEdit::onTreeViewSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{

  if (!deselected.isEmpty())
  {
    QModelIndex deselectedIndex = m_proxyModel->mapSelectionToSource(deselected).indexes().first();

  }

  if (!selected.isEmpty())
  {
    QModelIndex selectedIndex = m_proxyModel->mapSelectionToSource(selected).indexes().first();

    //selectedIndex

    qDebug() << "new selected index:" << selectedIndex;
    qDebug() << "parent of new selected index:" << selectedIndex.parent();
    TreeItem *item = static_cast<TreeItem*>(selectedIndex.internalPointer());
    qDebug() << "id:" << item->id();
    qDebug() << "";
  }
}

QModelIndex TreeEdit::selectedIndex()
{
  return m_proxyModel->mapToSource(ui->treeView->selectionModel()->currentIndex());
}

void TreeEdit::onResetRequired()
{
  m_treeModel->writeFile(); // TODO use something smarter - do not use hard drive

  // TODO is there another way of reseting?
  delete m_treeModel;
  delete m_proxyModel;

  setupModel();
}

void TreeEdit::setupModel()
{
  m_treeModel = new TreeModel(this);
  m_proxyModel = new ProxyModel(this);
  m_proxyModel->setSourceModel(m_treeModel);

  ui->treeView->setModel(m_proxyModel);
  ui->treeView->expandAll();

  connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &TreeEdit::onTreeViewSelectionChanged);
  connect(m_treeModel, &TreeModel::resetRequired, this, &TreeEdit::onResetRequired);
}

void TreeEdit::on_pushButton_clicked()
{
  qDebug() << "find and mark item with id:" << ui->spinBox->value();
  qDebug() << "found ids:" << getIds(QModelIndex());
}

QList<int> TreeEdit::getIds(QModelIndex parent)
{
  QList<int> ids;

  int i = 0;
  QModelIndex modelIndex = m_treeModel->index(i++, 0, parent);

  while (modelIndex.isValid())
  {
    ids << static_cast<TreeItem*>(modelIndex.internalPointer())->id();
    ids << getIds(modelIndex);
    modelIndex = m_treeModel->index(i++, 0, parent);
  }

  return ids;
}
