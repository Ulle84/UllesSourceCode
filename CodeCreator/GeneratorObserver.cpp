#include "ui_GeneratorObserver.h"

#include "Class.h"
#include "GeneratorObserver.h"
#include "XmlHelper.h"

GeneratorObserver::GeneratorObserver(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorObserver)
{
  ui->setupUi(this);

  connect(ui->lineEditSubject, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->lineEditObserver, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));

  connect(ui->checkBoxSubject, SIGNAL(clicked()), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxObserver, SIGNAL(clicked()), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxInterface, SIGNAL(clicked()), this, SIGNAL(optionsChanged()));
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
    else if (xml.name() == "CreateSubject")
    {
      XmlHelper::readXml(xml,  ui->checkBoxSubject);
    }
    else if (xml.name() == "CreateObserver")
    {
      XmlHelper::readXml(xml,  ui->checkBoxObserver);
    }
    else if (xml.name() == "CreateInterface")
    {
      XmlHelper::readXml(xml,  ui->checkBoxInterface);
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
  XmlHelper::writeXml(xml, "CreateSubject", ui->checkBoxSubject);
  XmlHelper::writeXml(xml, "CreateObserver", ui->checkBoxObserver);
  XmlHelper::writeXml(xml, "CreateInterface", ui->checkBoxInterface);
}

QList<QPair<QString, QString> > GeneratorObserver::generatedCode()
{
  QList<QPair<QString, QString> > code;

  QString subject = ui->lineEditSubject->text();
  QString observer = ui->lineEditObserver->text();

  if (ui->checkBoxSubject->isChecked())
  {
    Class c(subject);

    code.append(qMakePair(subject + ".h", c.declaration()));
    code.append(qMakePair(subject + ".cpp", c.implementation()));
  }

  if (ui->checkBoxObserver->isChecked())
  {
    Class c(observer);

    code.append(qMakePair(observer + ".h", c.declaration()));
    code.append(qMakePair(observer + ".cpp", c.implementation()));
  }

  if (ui->checkBoxInterface->isChecked())
  {

  }





  return code;

  /*
bool TemplateSubject::registerObserver(ITemplateObserver* observer)
{
  bool returnValue = false;

  if (observer != nullptr)
  {
    if (std::find(mObservers.begin(), mObservers.end(), observer) == mObservers.end())
    {
      mObservers.push_back(observer);
      returnValue = true;
    }
  }

  return returnValue;
}*/
}
