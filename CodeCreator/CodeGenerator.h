#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

class QStringList;

class HeaderOptions;
class ClassOptions;

class CodeGenerator
{
public:
  CodeGenerator();

  QStringList generateCodeHeader(const HeaderOptions& options);
  QStringList generateCodeClass(const ClassOptions& options);
  //QStringList generateCodePimpl();
};

#endif // CODEGENERATOR_H
