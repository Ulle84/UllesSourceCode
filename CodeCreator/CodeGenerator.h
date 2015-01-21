#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Options.h"

class QStringList;
class CodeSaver;

class CodeGenerator
{
public:
  CodeGenerator();
  ~CodeGenerator();

  void generateCode(const Options& options);

private:
  QStringList generateCodeHeader();
  //QStringList generateCodeClass();
  //QStringList generateCodePimpl();

  CodeSaver* m_codeSaver;
  Options m_options;
};

#endif // CODEGENERATOR_H
