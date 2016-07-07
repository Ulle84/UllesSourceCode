#ifndef GENERATORI_H
#define GENERATORI_H

#include <QList>
#include <QPair>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

class GeneratorI {
public:
  virtual ~GeneratorI(){}

  virtual void readXml(QXmlStreamReader& xml) = 0;
  virtual void writeXml(QXmlStreamWriter& xml) = 0;
  virtual QList<QPair<QString, QString> > generatedCode() = 0;

signals:
  virtual void optionsChanged() = 0;
};

#endif // GENERATORI_H
