#ifndef GENERATORINTERFACE_H
#define GENERATORINTERFACE_H

#include <QWidget>

#include "GeneratorI.h"
#include "Interface.h"

namespace Ui
{
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

private:
  Ui::GeneratorInterface* ui;
};

#endif // GENERATORINTERFACE_H
