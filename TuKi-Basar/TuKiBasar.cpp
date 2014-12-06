#include "TuKiBasar.h"
#include "ui_TuKiBasar.h"

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
