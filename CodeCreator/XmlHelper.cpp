#include <QCheckBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QStringList>

#include "XmlHelper.h"

void XmlHelper::writeXml(QXmlStreamWriter& xml, const QString &name, const QCheckBox* checkBox)
{
  xml.writeTextElement(name, checkBox->isChecked() ? "true" : "false");
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
