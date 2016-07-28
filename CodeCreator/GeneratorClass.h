#ifndef GENERATORCLASS_H
#define GENERATORCLASS_H

#include <QWidget>
#include <Qlist>

#include "GeneratorI.h"
#include "Interface.h"
#include "Members.h"

class QCompleter;
class CodeGenerator;
class WidgetListEditor;

namespace Ui
{
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
  void addMethod();
  void addMember();
  void on_pushButtonMethods_clicked();
  void on_pushButtonMembers_clicked();

private:
  void setConnections();
  void fillMethodList();
  void fillMemberList();

  Ui::GeneratorClass* ui;

  QCompleter* m_completer;
  Interface m_interface;
  Members m_members;
  WidgetListEditor* m_widgetListEditorMethods;
  WidgetListEditor* m_widgetListEditorMembers;
};

#endif // GENERATORCLASS_H
