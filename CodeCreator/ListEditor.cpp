#include "ListEditor.h"
#include "ui_ListEditor.h"

ListEditor::ListEditor(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ListEditor)
{
  ui->setupUi(this);
}

ListEditor::~ListEditor()
{
  delete ui;
}
