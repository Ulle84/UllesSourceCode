#include <QRegExp>

#include "ArticleReturn.h"
#include "ui_ArticleReturn.h"

ArticleReturn::ArticleReturn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArticleReturn)
{
    ui->setupUi(this);

    QRegExp rx ("[0-9]{6}");
    ui->lineEdit->setValidator(new QRegExpValidator (rx, this));
}

ArticleReturn::~ArticleReturn()
{
    delete ui;
}
