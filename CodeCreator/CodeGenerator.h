#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

class QStringList;

class CodeGenerator
{
public:
  CodeGenerator();

  QStringList generateCodeHeader();
  QStringList generateCodeClass();
  QStringList generateCodePimpl();
};

#endif // CODEGENERATOR_H
