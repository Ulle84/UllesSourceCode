#ifndef GENERATORITERFACE_H
#define GENERATORITERFACE_H

#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "Options.h"

class GeneratorInterface {
public:
  virtual void generate(const QString& folder) = 0;
  virtual void readXml(QXmlStreamReader& xml) = 0;
  virtual void writeXml(QXmlStreamWriter& xml) = 0;
};

#endif // GENERATORITERFACE_H
