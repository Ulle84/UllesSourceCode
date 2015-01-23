#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Options.h"

class QStringList;

class CodeGenerator
{
public:
  CodeGenerator();
  ~CodeGenerator();

  void copyFromTemplate(const Options& options);
};

#endif // CODEGENERATOR_H
