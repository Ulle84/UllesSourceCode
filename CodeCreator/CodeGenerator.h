#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <QWidget>
#include <QString>
#include "Options.h"

class QStringList;

class CodeGenerator  : public QWidget
{
  Q_OBJECT

public:
  explicit CodeGenerator(QWidget *parent = 0);
  ~CodeGenerator();

  void setBasePath(const QString& basePath);
  bool copyFromTemplate(const Options& options);

private:
  QString m_basePath;
};

#endif // CODEGENERATOR_H
