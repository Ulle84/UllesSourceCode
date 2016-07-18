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
    i.setForwardDeclaredClasses(QStringList() << observer + "I");

    Class c(subject);
    c.setInterfaces(QList<Interface>() << interface);
    c.setForwardDeclaredClasses(QStringList() << observer + "I");
    c.setDeclarationIncludes(QStringList() << "<vector>");
    c.setImplementationIncludes(QStringList() << "<algorithm>" << "\"" + observer + "I.h\"");

    Member member;
    member.setType("std::vector<const " + observer + "I*>");
    member.setName("observers");

    Members members;
    members.append(member);
    c.setMembers(members);

    code.append(qMakePair(i.name() + ".h", i.declaration()));
    code.append(qMakePair(c.name() + ".h", c.declaration()));
    code.append(qMakePair(c.name() + ".cpp", c.implementation()));

  }

  if (ui->checkBoxObserver->isChecked())
  {
    Class c(observer);
    Interface interface = ui->interfaceEditor->interface();
    interface.setName(observer + "I");
    c.setInterfaces(QList<Interface>() << interface);

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
  QString code;

  code.append("if (observer != nullptr)\n");
  code.append("{\n");
  code.append("  if (std::find(m_observers.begin(), m_observers.end(), observer) == m_observers.end())\n");
  code.append("  {\n");
  code.append("    m_observers.push_back(observer);\n");
  code.append("    return true;\n");
  code.append("  }\n");
  code.append("}\n");
  code.append("\n");
  code.append("return false");

  return code;
}

QString GeneratorObserver::unregisterObserverCode()
{
  QString code;

  code.append("if (observer != nullptr)\n");
  code.append("{\n");
  code.append("  for (auto it = m_observers.begin(); it != m_observers.end(); it++)\n");
  code.append("  {\n");
  code.append("    if (*it == observer)\n");
  code.append("    {\n");
  code.append("      m_observers.erase(it);\n");
  code.append("      return true;\n");
  code.append("    }\n");
  code.append("  }\n");
  code.append("}\n");
  code.append("\n");
  code.append("return false;\n");

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
