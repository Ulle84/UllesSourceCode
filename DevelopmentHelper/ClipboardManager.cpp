#include "ClipboardManager.h"
#include "ui_ClipboardManager.h"

ClipboardManager::ClipboardManager(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ClipboardManager)
{
  ui->setupUi(this);
}

ClipboardManager::~ClipboardManager()
{
  delete ui;
}
