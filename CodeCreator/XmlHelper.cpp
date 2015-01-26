#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QStringList>

#include "XmlHelper.h"

void XmlHelper::writeXml(QXmlStreamWriter& xml, const QString &name, const QCheckBox* checkBox)
{
  xml.writeTextElement(name, checkBox->isChecked() ? "true" : "false");
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

void XmlHelper::writeXml(QXmlStreamWriter& xml, const QString &name, const QLineEdit* lineEdit)
{
  xml.writeTextElement(name, lineEdit->text());
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

void XmlHelper::readXml(QXmlStreamReader &xml, QCheckBox* checkBox)
{
  checkBox->setChecked(xml.readElementText() == "true");
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

void XmlHelper::readXml(QXmlStreamReader &xml, QLineEdit* lineEdit)
{
  lineEdit->setText(xml.readElementText());
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
