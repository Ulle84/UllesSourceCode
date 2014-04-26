#include "doublebutton.h"
#include "ui_doublebutton.h"

#include <QMessageBox>

DoubleButton::DoubleButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoubleButton)
{
    ui->setupUi(this);
}

DoubleButton::~DoubleButton()
{
    delete ui;
}

void DoubleButton::on_pushButton1_clicked()
{
    QMessageBox messageBox;
    messageBox.setText(tr("Hello, I am button 1"));
    messageBox.exec();
}

void DoubleButton::on_pushButton2_clicked()
{
    QMessageBox messageBox;
    messageBox.setText(tr("Hello, I am button 1"));
    messageBox.exec();
}
