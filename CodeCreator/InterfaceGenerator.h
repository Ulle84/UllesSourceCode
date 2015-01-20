#ifndef INTERFACEGENERATOR_H
#define INTERFACEGENERATOR_H

#include <QWidget>

class CodeSaver;
class CodeGenerator;

namespace Ui {
class InterfaceGenerator;
}

class InterfaceGenerator : public QWidget
{
  Q_OBJECT
  
public:
  explicit InterfaceGenerator(CodeSaver* codeSaver, CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~InterfaceGenerator();
  
private:
  Ui::InterfaceGenerator *ui;

  CodeSaver* m_codeSaver;
  CodeGenerator* m_codeGenerator;
};

#endif // INTERFACEGENERATOR_H
