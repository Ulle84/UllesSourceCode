#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_returnPressed()
{
    bool conversionOkay;
    int time = ui->lineEdit->text().toInt(&conversionOkay, 10);

    if (conversionOkay)
    {
        ui->label->setText(QDateTime::fromTime_t(time).toString("yyyy-MM-dd hh:mm:ss"));
    }
    else
    {
        ui->label->setText("no valid input");
    }
}
