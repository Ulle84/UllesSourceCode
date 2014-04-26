#include "smalltest.h"
#include "ui_smalltest.h"

SmallTest::SmallTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmallTest)
{
    ui->setupUi(this);
}

SmallTest::~SmallTest()
{
    delete ui;
}

void SmallTest::on_pushButtonCommit_clicked()
{
    ui->plainTextEdit->appendPlainText(ui->lineEdit->text());
}
