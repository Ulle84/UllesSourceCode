#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile saveFile("/Users/Ulle/temp/test.txt");

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
    }

    QJsonObject jsonObject;

    QJsonArray jsonArray;
    for (int i = 0; i < 3; i++)
    {
        jsonArray.append(i+0.5);
        /*QJsonObject jsonObject;
        jsonObject["intTest"] = i;
        jsonArray.append(jsonObject);*/
    }

    jsonObject["arrayTest"] = jsonArray;

    for (int i = 0; i < 3; i++)
    {
        qDebug() << jsonObject["arrayTest"].toArray()[i].toDouble();
    }


    QJsonDocument jsonDocument(jsonObject);
    saveFile.write(jsonDocument.toJson());
}

MainWindow::~MainWindow()
{
    delete ui;
}
