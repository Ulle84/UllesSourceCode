#ifndef GeneratorDecorator_H
#define GeneratorDecorator_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

class WidgetListEditor;

namespace Ui
{
  class GeneratorDecorator;
}

class GeneratorDecorator : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit GeneratorDecorator(QWidget *parent = 0);
  ~GeneratorDecorator();

  // GeneratorI
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);
  QList<QPair<QString, QString> > generatedCode();

signals:
  void optionsChanged();

private:
  Ui::GeneratorDecorator* ui;
};

#endif // GeneratorDecorator_H
