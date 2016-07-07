#ifndef XMLHELPER_H
#define XMLHELPER_H

#include <QList>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class QCheckBox;
class QComboBox;
class QLineEdit;
class QPlainTextEdit;

class Method;
class Interface;
class Parameter;
class SelectorDeclarationType;
class SelectorSingletonType;
class SelectorDPointerType;

class XmlHelper
{
public:
  // QCheckBox
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const QCheckBox* checkBox);
  static void readXml(QXmlStreamReader& xml, QCheckBox* checkBox);

  // QComboBox
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const QComboBox* comboBox, bool writeOptions = true);
  static void readXml(QXmlStreamReader& xml, QComboBox* comboBox);

  // QLineEdit
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const QLineEdit* lineEdit);
  static void readXml(QXmlStreamReader& xml, QLineEdit* lineEdit);

  // QPlainTextEdit
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const QPlainTextEdit* plainTextEdit);
  static void readXml(QXmlStreamReader& xml, QPlainTextEdit* plainTextEdit);

  // SelectorDeclarationType
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const SelectorDeclarationType* selectorDeclarationType);
  static void readXml(QXmlStreamReader& xml, SelectorDeclarationType* selectorDeclarationType);

  // SelectorSingletonType
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const SelectorSingletonType* selectorSingletonType);
  static void readXml(QXmlStreamReader& xml, SelectorSingletonType* selectorSingletonType);

  // SelectorDeclarationType
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const SelectorDPointerType* selectorDPointerType);
  static void readXml(QXmlStreamReader& xml, SelectorDPointerType* selectorDPointerType);

  // QList<Interface>
  static void writeXml(QXmlStreamWriter& xml, const QString& name, const QList<Interface>* interfaces);
  static void readXml(QXmlStreamReader& xml, QList<Interface>* interfaces);

  // Interface
  static void writeXml(QXmlStreamWriter& xml, const Interface* interface);
  static void readXml(QXmlStreamReader& xml, Interface* interface);

  // Method
  static void writeXml(QXmlStreamWriter& xml, const Method* method);
  static void readXml(QXmlStreamReader& xml, Method* method);

  // Parameter
  static void writeXml(QXmlStreamWriter& xml, const Parameter* parameter);
  static void readXml(QXmlStreamReader& xml, Parameter* parameter);
};

#endif // XMLHELPER_H
