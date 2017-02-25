#include <QLayout>
#include <QLayoutItem>

#include "PathSelector.h"

#include "GridLayouter.h"
#include "ui_GridLayouter.h"

GridLayouter::GridLayouter(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GridLayouter)
{
  ui->setupUi(this);

  PathSelector* pathSelector1 = new PathSelector(this);
  pathSelector1->setLabelText("short");
  pathSelector1->setButtonText("looooooooooooooooooooooooooooooooooooooooong");

  PathSelector* pathSelector2 = new PathSelector(this);
  pathSelector2->setLabelText("looooooooooooooooooooooooooooooooooooooooong");
  pathSelector2->setButtonText("short");

  ui->verticalLayout->addWidget(pathSelector1);
  ui->verticalLayout->addWidget(pathSelector2);

  rearrangeInGrid();
}

GridLayouter::~GridLayouter()
{
  delete ui;
}

void GridLayouter::rearrangeInGrid()
{
  // iterate over all widgets in vertical layout
  int nWidgets = ui->verticalLayout->count();
  for (int i = 0; i < nWidgets; ++i)
  {
    QLayoutItem* layoutItem = ui->verticalLayout->itemAt(i);
    if (layoutItem)
    {
      QLayout* layout = layoutItem->widget()->layout();
      if (layout)
      {
        int nWidgets2 = layout->count();
        for (int j = 0; j < nWidgets2; ++j)
        {
          ui->gridLayout->addWidget(layout->takeAt(0)->widget(), i, j);
          //QLayoutItem* layoutItem = ;

        }
      }
    }


  }
}
