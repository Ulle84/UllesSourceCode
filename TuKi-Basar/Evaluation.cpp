#include "Evaluation.h"
#include "ui_Evaluation.h"

Evaluation::Evaluation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Evaluation)
{
    ui->setupUi(this);
}

Evaluation::~Evaluation()
{
    delete ui;
}
