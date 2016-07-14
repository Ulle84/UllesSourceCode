#include "ui_GeneratorObserver.h"

#include "GeneratorObserver.h"
#include "XmlHelper.h"

GeneratorObserver::GeneratorObserver(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorObserver)
{
  ui->setupUi(this);

  connect(ui->lineEditSubject, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->lineEditObserver, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorObserver::~GeneratorObserver()
{
  delete ui;
}

void GeneratorObserver::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Subject")
    {
      XmlHelper::readXml(xml,  ui->lineEditSubject);
    }
    else if (xml.name() == "Observer")
    {
      XmlHelper::readXml(xml,  ui->lineEditObserver);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorObserver::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Subject", ui->lineEditSubject);
  XmlHelper::writeXml(xml, "Observer", ui->lineEditObserver);
}

QList<QPair<QString, QString> > GeneratorObserver::generatedCode()
{
  QList<QPair<QString, QString> > code;

  QString subject = ui->lineEditSubject->text();
  QString observer = ui->lineEditObserver->text();

  code.append(qMakePair(subject + ".h", QString("TODO Declaration")));
  code.append(qMakePair(subject + ".cpp", QString("TODO Implementation")));

  code.append(qMakePair(observer + ".h", QString("TODO Declaration")));
  code.append(qMakePair(observer + ".cpp", QString("TODO Implementation")));

  return code;
}
