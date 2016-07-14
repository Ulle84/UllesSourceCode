#ifndef GeneratorTemplate_H
#define GeneratorTemplate_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

namespace Ui
{
  class GeneratorTemplate;
}

class GeneratorTemplate : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit GeneratorTemplate(QWidget *parent = 0);
  ~GeneratorTemplate();

  // GeneratorI
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);
  QList<QPair<QString, QString> > generatedCode();

signals:
  void optionsChanged();

private:
  Ui::GeneratorTemplate* ui;
};

#endif // GeneratorTemplate_H
