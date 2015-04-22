#include "Widget.h"
#include "ui_Widget.h"

#include <QString>
#include <QByteArray>

Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
}

Widget::~Widget()
{
  delete ui;
}

void Widget::on_lineEditPlainText_editingFinished()
{
  QByteArray ba;
  ba.append(ui->lineEditPlainText->text());
  ui->lineEditBase64EncodedText->setText(ba.toBase64().data());
}

void Widget::on_lineEditBase64EncodedText_editingFinished()
{
  QByteArray ba;
  ba.append(ui->lineEditBase64EncodedText->text());
  ui->lineEditPlainText->setText(QByteArray::fromBase64(ba).data());
}
