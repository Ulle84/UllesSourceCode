#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QStringList>

#include "Interface.h"
#include "SelectorDeclarationType.h"
#include "SelectorDPointerType.h"
#include "SelectorSingletonType.h"
#include "XmlHelper.h"
#include "Member.h"

void XmlHelper::writeXml(QXmlStreamWriter& xml, const QString &name, const QCheckBox* checkBox)
{
  xml.writeTextElement(name, checkBox->isChecked() ? "true" : "false");
}

void XmlHelper::readXml(QXmlStreamReader &xml, QCheckBox* checkBox)
{
  checkBox->setChecked(xml.readElementText() == "true");
}

void XmlHelper::writeXml(QXmlStreamWriter &xml, const QString &name, const QComboBox *comboBox, bool writeOptions)
{
  xml.writeStartElement(name);

  if (writeOptions)
  {
    xml.writeStartElement("Options");
    for (int i = 0; i < comboBox->count(); i++)
    {
      xml.writeTextElement("Option", comboBox->itemText(i));
    }
    xml.writeEndElement(); // Options
  }

  xml.writeTextElement("Selected", comboBox->currentText());

  xml.writeEndElement();
}

void XmlHelper::readXml(QXmlStreamReader &xml, QComboBox *comboBox)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Options")
    {
      QStringList options;
      while (xml.readNextStartElement())
      {
        if (xml.name() == "Option")
        {
          options.append(xml.readElementText());
        }
        else
        {
          xml.skipCurrentElement();
        }
      }
      comboBox->insertItems(0, options);
    }
    else if (xml.name() == "Selected")
    {
      comboBox->setCurrentIndex(comboBox->findText(xml.readElementText()));
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void XmlHelper::writeXml(QXmlStreamWriter& xml, const QString &name, const QLineEdit* lineEdit)
{
  xml.writeTextElement(name, lineEdit->text());
}

void XmlHelper::readXml(QXmlStreamReader &xml, QLineEdit* lineEdit)
{
  lineEdit->setText(xml.readElementText());
}

void XmlHelper::writeXml(QXmlStreamWriter& xml, const QString &name, const QPlainTextEdit* plainTextEdit)
{
  xml.writeStartElement(name);
  QStringList lines = plainTextEdit->toPlainText().split("\n");
  for (auto it = lines.begin(); it != lines.end(); it++)
  {
    xml.writeTextElement("Line", *it);
  }
  xml.writeEndElement();
}

void XmlHelper::readXml(QXmlStreamReader &xml, QPlainTextEdit* plainTextEdit)
{
  QStringList lines;
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Line")
    {
      lines.append(xml.readElementText());
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
  plainTextEdit->setPlainText(lines.join("\n"));
}

void XmlHelper::writeXml(QXmlStreamWriter &xml, const QString &name, const SelectorDeclarationType *selectorDeclarationType)
{
  xml.writeTextElement(name, QString::number(selectorDeclarationType->declarationType()));
}

void XmlHelper::readXml(QXmlStreamReader &xml, SelectorDeclarationType *selectorDeclarationType)
{
  selectorDeclarationType->setDeclarationType(static_cast<Class::DeclarationType>(xml.readElementText().toInt()));
}

void XmlHelper::writeXml(QXmlStreamWriter &xml, const QString &name, const SelectorSingletonType *selectorSingletonType)
{
  xml.writeTextElement(name, QString::number(selectorSingletonType->singletonType()));
}

void XmlHelper::readXml(QXmlStreamReader &xml, SelectorSingletonType *selectorSingletonType)
{
  selectorSingletonType->setSingletonType(static_cast<Class::SingletonType>(xml.readElementText().toInt()));
}

void XmlHelper::writeXml(QXmlStreamWriter &xml, const QString &name, const SelectorDPointerType *selectorDPointerType)
{
  xml.writeTextElement(name, QString::number(selectorDPointerType->dPointerType()));
}

void XmlHelper::readXml(QXmlStreamReader &xml, SelectorDPointerType *selectorDPointerType)
{
  selectorDPointerType->setDPointerType(static_cast<Class::DPointerType>(xml.readElementText().toInt()));
}

void XmlHelper::writeXml(QXmlStreamWriter& xml, const QString& name, const QList<Interface>* interfaces)
{
  xml.writeStartElement(name);

  for (auto it = interfaces->begin(); it != interfaces->end(); it++)
  {
    writeXml(xml, &(*it));
  }

  xml.writeEndElement();
}

void XmlHelper::readXml(QXmlStreamReader& xml, QList<Interface>* interfaces)
{
  interfaces->clear();

  while (xml.readNextStartElement())
  {
    if (xml.name() == "Interface")
    {
      Interface interface;
      readXml(xml, &interface);
      interfaces->append(interface);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void XmlHelper::writeXml(QXmlStreamWriter& xml, const Interface* interface, const QString& name)
{
  xml.writeStartElement(name);

  xml.writeTextElement("Name", interface->name());
  xml.writeTextElement("ToImplement", interface->isToImplement() ? "true" : "false");

  for (auto it = interface->begin(); it != interface->end(); it++)
  {
    writeXml(xml, &(*it));
  }

  xml.writeEndElement();
}

void XmlHelper::readXml(QXmlStreamReader& xml, Interface* interface)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      interface->setName(xml.readElementText());
    }
    else if (xml.name() == "ToImplement")
    {
      interface->setToImplement(xml.readElementText() == "true");
    }
    else if (xml.name() == "Method")
    {
      Method method;
      readXml(xml, &method);
      interface->append(method);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void XmlHelper::writeXml(QXmlStreamWriter& xml, const Method* method)
{
  xml.writeStartElement("Method");

  xml.writeTextElement("Type", QString::number(method->type()));
  xml.writeTextElement("DeclarationType", QString::number(method->declarationType()));
  xml.writeTextElement("Name", method->name());
  xml.writeTextElement("ReturnType", method->returnType());

  for (auto it = method->begin(); it != method->end(); it++)
  {
    writeXml(xml, &(*it));
  }

  xml.writeEndElement();
}

void XmlHelper::readXml(QXmlStreamReader& xml, Method* method)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Type")
    {
      method->setType(static_cast<Method::Type>(xml.readElementText().toInt()));
    }
    else if (xml.name() == "DeclarationType")
    {
      method->setDeclarationType(static_cast<Method::DeclarationType>(xml.readElementText().toInt()));
    }
    else if (xml.name() == "Name")
    {
      method->setName(xml.readElementText());
    }
    else if (xml.name() == "ReturnType")
    {
      method->setReturnType(xml.readElementText());
    }
    else if (xml.name() == "Parameter")
    {
      Parameter parameter;
      readXml(xml, &parameter);
      method->append(parameter);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void XmlHelper::writeXml(QXmlStreamWriter& xml, const Parameter* parameter)
{
  xml.writeStartElement("Parameter");

  xml.writeTextElement("Type", parameter->type());
  xml.writeTextElement("Name", parameter->name());
  xml.writeTextElement("DefaultValue", parameter->defaultValue());

  xml.writeEndElement();
}

void XmlHelper::readXml(QXmlStreamReader& xml, Parameter* parameter)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Type")
    {
      parameter->setType(xml.readElementText());
    }
    else if (xml.name() == "Name")
    {
      parameter->setName(xml.readElementText());
    }
    else if (xml.name() == "DefaultValue")
    {
      parameter->setDefaultValue(xml.readElementText());
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void XmlHelper::writeXml(QXmlStreamWriter &xml, const QString &name, const QList<Member> *members)
{
  xml.writeStartElement(name);

  for (auto it = members->begin(); it != members->end(); it++)
  {
    writeXml(xml, &(*it));
  }

  xml.writeEndElement();
}

void XmlHelper::readXml(QXmlStreamReader &xml, QList<Member> *members)
{
  members->clear();

  while (xml.readNextStartElement())
  {
    if (xml.name() == "Member")
    {
      Member member;
      readXml(xml, &member);
      members->append(member);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void XmlHelper::writeXml(QXmlStreamWriter &xml, const Member *member)
{
  xml.writeStartElement("Member");

  xml.writeTextElement("Type", member->type());
  xml.writeTextElement("Name", member->name());
  xml.writeTextElement("DefaultValue", member->defaultValue());
  xml.writeTextElement("DeclarationType", QString::number(member->declarationType()));
  xml.writeTextElement("Getter", member->hasGetter() ? "true" : "false");
  xml.writeTextElement("Setter", member->hasSetter() ? "true" : "false");

  xml.writeEndElement();
}

void XmlHelper::readXml(QXmlStreamReader &xml, Member *member)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Type")
    {
      member->setType(xml.readElementText());
    }
    else if (xml.name() == "Name")
    {
      member->setName(xml.readElementText());
    }
    else if (xml.name() == "DefaultValue")
    {
      member->setDefaultValue(xml.readElementText());
    }
    else if (xml.name() == "DeclarationType")
    {
      member->setDeclarationType(static_cast<Member::DeclarationType>(xml.readElementText().toInt()));
    }
    else if (xml.name() == "Getter")
    {
      member->setGetter(xml.readElementText() == "true");
    }
    else if (xml.name() == "Setter")
    {
      member->setSetter(xml.readElementText() == "true");
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}
