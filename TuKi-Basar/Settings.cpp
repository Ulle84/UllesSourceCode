#include "Settings.h"
#include "ui_Settings.h"

#include <QMessageBox>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

int Settings::getPc()
{
    return ui->spinBoxPc->value();
}

int Settings::getProductMin()
{
    return ui->spinBoxProductMin->value();
}

int Settings::getProductMax()
{
    return ui->spinBoxProductMax->value();
}

int Settings::getSellerMin()
{
    return ui->spinBoxSellerMin->value();
}

int Settings::getSellerMax()
{
    return ui->spinBoxSellerMax->value();
}

void Settings::on_pushButtonOk_clicked()
{
    if (ui->spinBoxSellerMax->value() < ui->spinBoxSellerMin->value())
    {
        QMessageBox mb;
        mb.setText(tr("Die maximale Verkäufernummer darf nicht kleiner als die minimale Verkäufernummer sein!"));
        mb.exec();
        return;
    }

    if (ui->spinBoxProductMax->value() < ui->spinBoxProductMin->value())
    {
        QMessageBox mb;
        mb.setText(tr("Die maximale Produktnummer darf nicht kleiner als die minimale Produktnummer sein!"));
        mb.exec();
        return;
    }

    this->accept();
}
