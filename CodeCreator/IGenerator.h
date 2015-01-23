#ifndef IGENERATOR_H
#define IGENERATOR_H

#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

class IGenerator {
public:
  virtual void generate(const QString& folder) = 0;
  virtual void readXml(QXmlStreamReader& xml) = 0;
  virtual void writeXml(QXmlStreamWriter& xml) = 0;
};

#endif // IGENERATOR_H
