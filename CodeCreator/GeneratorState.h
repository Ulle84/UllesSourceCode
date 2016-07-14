#ifndef GeneratorState_H
#define GeneratorState_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"
#include "Interface.h"

class WidgetListEditor;

namespace Ui
{
  class GeneratorState;
}

class GeneratorState : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit GeneratorState(QWidget *parent = 0);
  ~GeneratorState();

  // GeneratorI
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);
  QList<QPair<QString, QString> > generatedCode();

signals:
  void optionsChanged();

private slots:
  void on_pushButtonInterface_clicked();
  void addMethod();

private:
  void fillMethodList();

  Ui::GeneratorState* ui;

  WidgetListEditor* m_widgetListEditor;
  Interface m_interface;
};

#endif // GeneratorState_H
