#include "Widget.h"
#include "ui_Widget.h"

#include <QCryptographicHash>
#include <QClipboard>

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

void Widget::on_lineEditInput_textChanged(const QString &arg1)
{
    QByteArray inputBytes(arg1.toUtf8());
    QByteArray myHash = QCryptographicHash::hash(inputBytes, QCryptographicHash::Sha1);
    QString result(myHash.toHex());

    ui->lineEditOutput->setText(result);
}

void Widget::on_pushButton_clicked()
{
    QApplication::clipboard()->setText(ui->lineEditOutput->text());
}
