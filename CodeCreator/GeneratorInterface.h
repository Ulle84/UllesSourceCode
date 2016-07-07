#ifndef GENERATORINTERFACE_H
#define GENERATORINTERFACE_H

#include <QWidget>

#include "GeneratorI.h"
#include "Interface.h"

class CodeGenerator;
class WidgetListEditor;

namespace Ui {
class GeneratorInterface;
}

class GeneratorInterface : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit GeneratorInterface(QWidget *parent = 0);
  ~GeneratorInterface();

  // GeneratorI
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);
  QList<QPair<QString, QString> > generatedCode();

signals:
  void optionsChanged();

private slots:
  void on_pushButtonDefineMethods_clicked();

  void addMethod();

private:
  void fillMethodList();

  Ui::GeneratorInterface* ui;

  WidgetListEditor* m_widgetListEditor;
  Interface m_interface;
};

#endif // GENERATORINTERFACE_H
