#include <QClipboard>

#include "SlashConverter.h"
#include "ui_SlashConverter.h"

SlashConverter::SlashConverter(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::SlashConverter)
{
  ui->setupUi(this);
}

SlashConverter::~SlashConverter()
{
  delete ui;
}

void SlashConverter::on_pushButtonConvertToBackslash_clicked()
{
  QString converted = ui->lineEdit->text().replace("/", "\\");
  updateText(converted);
}

void SlashConverter::on_pushButtonConvertToFowardSlash_clicked()
{
  QString converted = ui->lineEdit->text().replace("\\", "/");
  updateText(converted);
}

void SlashConverter::updateText(const QString& text)
{
  ui->lineEdit->setText(text);
  QApplication::clipboard()->setText(text);
}
