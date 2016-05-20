#include "CodeCleaner.h"
#include "CodeCleanerGui.h"
#include "ui_CodeCleanerGui.h"

CodeCleanerGui::CodeCleanerGui(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeCleanerGui)
{
  ui->setupUi(this);
}

CodeCleanerGui::~CodeCleanerGui()
{
  delete ui;
}

void CodeCleanerGui::on_plainTextEditInput_textChanged()
{
  CodeCleaner codeCleaner(ui->plainTextEditInput->toPlainText());
  codeCleaner.process();
  ui->plainTextEditOutput->setPlainText(codeCleaner.getCode());
}
