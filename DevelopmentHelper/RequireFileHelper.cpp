#include <QFile>
#include <QMessageBox>
#include <QDebug>

#include "RequireFileHelper.h"
#include "ui_RequireFileHelper.h"

RequireFileHelper::RequireFileHelper(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::RequireFileHelper)
{
  ui->setupUi(this);
}

RequireFileHelper::~RequireFileHelper()
{
  delete ui;
}

void RequireFileHelper::setFile(QString fileName)
{
    this->fileName = fileName;
    ui->labelFileName->setText(fileName);

    readFile();
}

void RequireFileHelper::readFile()
{
    QFile* file = new QFile(fileName);
    if (!file->open(QFile::ReadWrite | QIODevice::Text))
    {
        QMessageBox::information(this, tr("error"), tr("can not open file"));
        return;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;
    if (!domDocument.setContent(file, true, &errorStr, &errorLine, &errorColumn))
    {
        QString errorString = tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr);
        QMessageBox::information(this, tr("XML parse error"), errorString);
        return;
    }
    file->close();

    major = readInt("major");
    minor = readInt("minor");
    fixlevel = readInt("fixlevel");

    updateVersionLabel();
}

void RequireFileHelper::updateFile()
{
    writeInt("major", major);
    writeInt("minor", minor);
    writeInt("fixlevel", fixlevel);
    writeFile();
    updateVersionLabel();
}

void RequireFileHelper::writeFile()
{
    QFile* file = new QFile(fileName);
    if (!file->open(QFile::ReadWrite | QIODevice::Text))
    {
        QMessageBox::information(this, tr("error"), tr("can not open file"));
        return;
    }

    file->resize(0);
    QTextStream stream(file);
    stream.setDevice(file);
    domDocument.save(stream, 2);

    file->close();
}

int RequireFileHelper::readInt(QString tagName)
{
    int returnValue = 0;
    QDomNodeList domNodeList = domDocument.elementsByTagName(tagName);
    if (domNodeList.length() == 0)
    {
        QMessageBox::information(this, tr("error"), tr("no %1 found").arg(tagName));
        return -1;
    }
    returnValue = domNodeList.at(0).toElement().text().toInt();
    qDebug() << QString("%1: %2").arg(tagName).arg(returnValue);
    return returnValue;
}

void RequireFileHelper::writeInt(QString tagName, int value)
{
    QDomNodeList domNodeList = domDocument.elementsByTagName(tagName);
    if (domNodeList.length() == 0)
    {
        QMessageBox::information(this, tr("error"), tr("no %1 found").arg(tagName));
        return;
    }
    domNodeList.at(0).firstChild().setNodeValue(QString("%1").arg(value));
}

void RequireFileHelper::on_pushButtonFixlevel_clicked()
{
    fixlevel++;
    updateFile();
}

void RequireFileHelper::on_pushButtonMajor_clicked()
{
    fixlevel = 0;
    minor = 0;
    major++;
    updateFile();
}

void RequireFileHelper::on_pushButtonMinor_clicked()
{
    fixlevel = 0;
    minor++;
    updateFile();
}


void RequireFileHelper::updateVersionLabel()
{
    ui->labelVersion->setText(QString("%1.%2.%3").arg(major).arg(minor).arg(fixlevel));
}
