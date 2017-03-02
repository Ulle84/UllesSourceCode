#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QFile>
#include <QDebug>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_settings = new QSettings("Ulle", "JsonTest", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  delete ui;
}

void MainWindow::writeTestFile(const QString &path)
{
  QFile file(path);

  if (!file.open(QIODevice::WriteOnly))
  {
    qWarning("Couldn't open save file.");
  }


  file.write(createTestObjectString());
  file.close();
}

QByteArray MainWindow::createTestObjectString()
{
  QJsonObject jsonObject;

  QJsonArray jsonArray;
  for (int i = 0; i < 3; i++)
  {
    jsonArray.append(i+0.5);
  }

  QJsonObject jsonSubObject;
  jsonSubObject["int"] = 100;
  jsonSubObject["double"] = 9.983484;
  jsonSubObject["bool"] = true;
  jsonSubObject["string"] = QString("helloWorld");

  jsonObject["arrayTest"] = jsonArray;
  jsonObject["jsonSubObject"] = jsonSubObject;

  for (int i = 0; i < 3; i++)
  {
    qDebug() << jsonObject["arrayTest"].toArray()[i].toDouble();
  }


  QJsonDocument jsonDocument(jsonObject);
  return jsonDocument.toJson();
}

void MainWindow::on_pushButtonWriteTestFile_clicked()
{
  writeTestFile("/Users/Ulle/temp/test.txt");
}

void MainWindow::on_pushButtonWriteTestOutput_clicked()
{
  ui->plainTextEditJson->clear();
  ui->plainTextEditJson->appendPlainText(createTestObjectString());
}
