#include <QDebug>

#include "WidgetListItem.h"
#include "WidgetListEditor.h"
#include "ui_WidgetListEditor.h"

WidgetListEditor::WidgetListEditor(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::WidgetListEditor)
{
  ui->setupUi(this);
  ui->pushButtonAdd->setText("test");
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

QList<QWidget*> WidgetListEditor::items()
{
  QList<QWidget*> list;

  for (int i = 0; i < ui->list->count(); i++)
  {
    QLayoutItem* layoutItem = ui->list->itemAt(i);
    if (layoutItem)
    {
      WidgetListItem* widgetListItem = dynamic_cast<WidgetListItem*>(layoutItem->widget());
      if (widgetListItem)
      {
        QWidget* item = widgetListItem->item();
        if (item != NULL)
        {
          list.append(item);
        }
      }
    }
  }

  return list;
}

void WidgetListEditor::clear()
{
  while(ui->list->itemAt(0))
  {
    QLayoutItem* layoutItem = ui->list->takeAt(0);
    if (layoutItem->widget())
    {
      delete layoutItem->widget();
    }
    delete layoutItem;
  }
}

void WidgetListEditor::setButtonText(const QString& buttonText)
{
  ui->pushButtonAdd->setText(buttonText);
}

void WidgetListEditor::on_pushButtonAdd_clicked()
{
  emit addClicked();
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
