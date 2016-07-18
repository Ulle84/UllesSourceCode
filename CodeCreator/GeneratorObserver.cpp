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

  connect(ui->interfaceEditor, SIGNAL(interfaceChanged()), this, SIGNAL(optionsChanged()));
}

QList<QPair<QString, QString> > GeneratorObserver::generatedCode()
{
  QList<QPair<QString, QString> > code;

  QString subject = ui->lineEditSubject->text();
  QString observer = ui->lineEditObserver->text();

  if (ui->checkBoxSubject->isChecked())
  {

    Interface interface;
    interface.setName(subject + "I");
    interface.append(Method("bool registerObserver(const " + observer + "I* observer)", registerObserverCode()));
    interface.append(Method("bool unregisterObserver(const " + observer + "I* observer)", unregisterObserverCode()));
    interface.append(Method("bool notifyObservers()", notifyObserversCode()));

    Class i(subject + "I");
    i.setInterface(interface, true);

    Class c(subject);
    c.setInterfaces(QList<Interface>() << interface);

    code.append(qMakePair(i.name() + ".h", i.declaration()));
    code.append(qMakePair(c.name() + ".h", c.declaration()));
    code.append(qMakePair(c.name() + ".cpp", c.implementation()));

  }

  if (ui->checkBoxObserver->isChecked())
  {
    Class c(observer);

    code.append(qMakePair(c.name() + ".h", c.declaration()));
    code.append(qMakePair(c.name() + ".cpp", c.implementation()));
  }

  if (ui->checkBoxInterface->isChecked())
  {
    Class c(observer + "I");
    c.setInterface(ui->interfaceEditor->interface(), true);

    code.append(qMakePair(c.name() + ".h", c.declaration()));
  }

  return code;
}

QString GeneratorObserver::registerObserverCode()
{
/*
bool returnValue = false;

  if (observer != nullptr)
  {
    if (std::find(mObservers.begin(), mObservers.end(), observer) == mObservers.end())
    {
      mObservers.push_back(observer);
      returnValue = true;
    }
  }

  return returnValue;*/

  QString code = "tst registerObserverCode";

  return code;
}

QString GeneratorObserver::unregisterObserverCode()
{
  /*
bool returnValue = false;

  if (observer != nullptr)
  {
    for (auto it = mObservers.begin(); it != mObservers.end(); it++)
    {
      if (*it == observer)
      {
        mObservers.erase(it);
        returnValue = true;
        break;
      }
    }
  }

  return returnValue;*/
  QString code = "tst unregisterObserverCode";

  return code;
}

QString GeneratorObserver::notifyObserversCode()
{
  QString code;

  code.append("for (auto it = m_observers.begin(); it != m_observers.end(); it++)\n");
  code.append("{\n");
  code.append("  // TODO check following code\n");

  Interface interface = ui->interfaceEditor->interface();
  for (auto it = interface.begin(); it != interface.end(); it++)
  {
    code.append("  (*it)->");
    code.append(it->name());
    code.append("();\n");
  }

  code.append("}");


  return code;
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
    else if (xml.name() == "ObserverInterface")
    {
      Interface interface;
      XmlHelper::readXml(xml, &interface);
      ui->interfaceEditor->setInterface(interface);
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
  XmlHelper::writeXml(xml, &ui->interfaceEditor->interface(), "ObserverInterface");
  XmlHelper::writeXml(xml, "CreateSubject", ui->checkBoxSubject);
  XmlHelper::writeXml(xml, "CreateObserver", ui->checkBoxObserver);
  XmlHelper::writeXml(xml, "CreateInterface", ui->checkBoxInterface);
}
