#include "TuKiBasar.h"
#include "ui_TuKiBasar.h"

#include "Settings.h"

TuKiBasar::TuKiBasar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TuKiBasar)
{
    ui->setupUi(this);
}

TuKiBasar::~TuKiBasar()
{
    delete ui;
}

void TuKiBasar::on_pushButton_clicked()
{
    Settings settings(this);
    settings.exec();
}
