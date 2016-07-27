#ifndef GeneratorAbstractFactory_H
#define GeneratorAbstractFactory_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

namespace Ui
{
  class GeneratorAbstractFactory;
}

class GeneratorAbstractFactory : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit GeneratorAbstractFactory(QWidget *parent = 0);
  ~GeneratorAbstractFactory();

  // GeneratorI
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);
  QList<QPair<QString, QString> > generatedCode();

signals:
  void optionsChanged();

private:
  Ui::GeneratorAbstractFactory* ui;
};

#endif // GeneratorAbstractFactory_H
