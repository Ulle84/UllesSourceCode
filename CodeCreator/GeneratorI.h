#ifndef GENERATORI_H
#define GENERATORI_H

#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

class GeneratorI {
public:
  virtual ~GeneratorI(){}

  virtual bool generate(const QString& folder) = 0;
  virtual void readXml(QXmlStreamReader& xml) = 0;
  virtual void writeXml(QXmlStreamWriter& xml) = 0;
};

#endif // GENERATORI_H
