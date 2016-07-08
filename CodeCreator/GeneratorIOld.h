#ifndef GENERATORIOLD_H
#define GENERATORIOLD_H

#include <QList>
#include <QPair>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

class GeneratorIOld {
public:
  virtual ~GeneratorIOld(){}

  bool generate(const QString& folder);
  virtual void readXml(QXmlStreamReader& xml) = 0;
  virtual void writeXml(QXmlStreamWriter& xml) = 0;
};

#endif // GENERATORIOLD_H
