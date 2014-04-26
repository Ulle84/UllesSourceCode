#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMessageBox messageBox(this);
    messageBox.setText("test");
    messageBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
