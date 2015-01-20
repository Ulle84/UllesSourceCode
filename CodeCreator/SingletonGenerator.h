#ifndef SINGLETONGENERATOR_H
#define SINGLETONGENERATOR_H

#include <QWidget>

class CodeSaver;
class CodeGenerator;

namespace Ui {
class SingletonGenerator;
}

class SingletonGenerator : public QWidget
{
  Q_OBJECT
  
public:
  explicit SingletonGenerator(CodeSaver* codeSaver, CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~SingletonGenerator();
  
private:
  Ui::SingletonGenerator *ui;

  CodeSaver* m_codeSaver;
  CodeGenerator* m_codeGenerator;
};

#endif // SINGLETONGENERATOR_H
