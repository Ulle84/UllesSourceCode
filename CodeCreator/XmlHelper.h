#ifndef XMLHELPER_H
#define XMLHELPER_H

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class QCheckBox;
class QComboBox;
class QLineEdit;
class QPlainTextEdit;

class XmlHelper
{
public:
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const QCheckBox* checkBox);
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const QComboBox* comboBox, bool writeOptions = true);
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const QLineEdit* lineEdit);
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const QPlainTextEdit* plainTextEdit);

  static void readXml(QXmlStreamReader& xml, QCheckBox* checkBox);
  static void readXml(QXmlStreamReader& xml, QComboBox* comboBox);
  static void readXml(QXmlStreamReader& xml, QLineEdit* lineEdit);
  static void readXml(QXmlStreamReader& xml, QPlainTextEdit* plainTextEdit);
};

#endif // XMLHELPER_H
