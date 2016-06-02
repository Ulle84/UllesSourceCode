#include <QDebug>

#include "WidgetListItem.h"
#include "WidgetListEditor.h"
#include "ui_WidgetListEditor.h"

WidgetListEditor::WidgetListEditor(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::WidgetListEditor)
{
  ui->setupUi(this);
}

WidgetListEditor::~WidgetListEditor()
{
  delete ui;
}

void WidgetListEditor::addItem(QWidget *item)
{
  WidgetListItem* widgetListItem = new WidgetListItem(this);
  widgetListItem->setItem(item);
  ui->list->addWidget(widgetListItem);

  connect(widgetListItem, SIGNAL(deleteItem()), this, SLOT(on_deleteItem()));
  connect(widgetListItem, SIGNAL(moveUp()), this, SLOT(on_moveUp()));
  connect(widgetListItem, SIGNAL(moveDown()), this, SLOT(on_moveDown()));
}

void WidgetListEditor::on_pushButtonAdd_clicked()
{
  emit pushButtonAddClicked();
}

void WidgetListEditor::on_deleteItem()
{
  int index = ui->list->indexOf(dynamic_cast<QWidget*>(QObject::sender()));

  QLayoutItem* item = ui->list->takeAt(index);

  if (item->widget())
  {
    delete item->widget();
  }

  delete item;
}

void WidgetListEditor::on_moveUp()
{
  int index = ui->list->indexOf(dynamic_cast<QWidget*>(QObject::sender()));

  if (index == 0)
  {
    return;
  }

  QLayoutItem* item = ui->list->takeAt(index);
  ui->list->insertItem(index - 1, item);
}

void WidgetListEditor::on_moveDown()
{
  int index = ui->list->indexOf(dynamic_cast<QWidget*>(QObject::sender()));

  if (index == ui->list->count() - 1)
  {
    return;
  }

  QLayoutItem* item = ui->list->takeAt(index);
  ui->list->insertItem(index + 1, item);
}

void WidgetListEditor::on_buttonBox_accepted()
{
  accept();
}

void WidgetListEditor::on_buttonBox_rejected()
{
  reject();
}
