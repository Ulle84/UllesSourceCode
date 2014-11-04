#include "ClipboardExtended.h"
#include "ui_ClipboardExtended.h"

ClipboardExtended::ClipboardExtended(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ClipboardExtended)
{
  ui->setupUi(this);
}

ClipboardExtended::~ClipboardExtended()
{
  delete ui;
}
