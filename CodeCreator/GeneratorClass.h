#ifndef GENERATORCLASS_H
#define GENERATORCLASS_H

#include <QWidget>
#include <Qlist>

#include "GeneratorI.h"
#include "Interface.h"

class QCompleter;
class CodeGenerator;
class WidgetListEditor;

namespace Ui {
class GeneratorClass;
}

class GeneratorClass : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit GeneratorClass(QWidget *parent = 0);
  ~GeneratorClass();

  // GeneratorI
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);
  QList<QPair<QString, QString> > generatedCode();

signals:
  void optionsChanged();

private slots:
  void on_singleton_singletonTypeChanged(int singletonType);
  void on_dPointer_dPointerTypeChanged(int dPointerType);
  void addInterface();
  void addMethod();
  void on_pushButtonInterfaces_clicked();
  void on_pushButtonMethods_clicked();

private:
  void setConnections();
  void fillInterfaceList();
  void fillMethodList();

  Ui::GeneratorClass* ui;

  QCompleter* m_completer;
  QList<Interface> m_interfaces;
  Interface m_interface;
  WidgetListEditor* m_widgetListEditorInterfaces;
  WidgetListEditor* m_widgetListEditorMethods;
};

#endif // GENERATORCLASS_H
