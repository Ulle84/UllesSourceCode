#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <QWidget>
#include "Options.h"

class QStringList;

class CodeGenerator  : public QWidget
{
  Q_OBJECT

public:
  explicit CodeGenerator(QWidget *parent = 0);
  ~CodeGenerator();

  bool copyFromTemplate(const Options& options);
};

#endif // CODEGENERATOR_H
