#ifndef GeneratorObserver_H
#define GeneratorObserver_H

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

#include "GeneratorI.h"

namespace Ui
{
  class GeneratorObserver;
}

class GeneratorObserver : public QWidget, public GeneratorI
{
  Q_OBJECT

public:
  explicit GeneratorObserver(QWidget *parent = 0);
  ~GeneratorObserver();

  // GeneratorI
  void readXml(QXmlStreamReader& xml);
  void writeXml(QXmlStreamWriter& xml);
  QList<QPair<QString, QString> > generatedCode();

signals:
  void optionsChanged();

private:
  QString registerObserverCode();
  QString unregisterObserverCode();
  QString notifyObserversCode();
  QString testCode();

  Ui::GeneratorObserver* ui;
};

#endif // GeneratorObserver_H
