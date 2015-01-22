#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Options.h"

class QStringList;

class CodeGenerator
{
public:
  CodeGenerator();
  ~CodeGenerator();

  void generateCode(const Options& options);

private:
  bool saveCode(const QString& fileName, const QStringList& code);

  void generateCodeHeader();
  void generateCodeClass();
  void generateCodePimpl();

  Options m_options;
};

#endif // CODEGENERATOR_H
