#include "WidgetListItem.h"
#include "ui_WidgetListItem.h"

WidgetListItem::WidgetListItem(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::WidgetListItem)
{
  ui->setupUi(this);
}

WidgetListItem::~WidgetListItem()
{
  delete ui;
}

void WidgetListItem::setItem(QWidget *item)
{
  ui->item->addWidget(item);
}

void WidgetListItem::on_pushButtonDelete_clicked()
{
  emit deleteItem();
}

void WidgetListItem::on_pushButtonUp_clicked()
{
  emit moveUp();
}

void WidgetListItem::on_pushButtonDown_clicked()
{
  emit moveDown();
}
