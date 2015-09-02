#include "SlashConverter.h"

#include "TextConverter.h"
#include "ui_TextConverter.h"

TextConverter::TextConverter(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TextConverter)
{
  ui->setupUi(this);

  SlashConverter* slashConverter = new SlashConverter(this);
  ui->groupBoxSlashConverter->layout()->addWidget(slashConverter);
}

TextConverter::~TextConverter()
{
  delete ui;
}
