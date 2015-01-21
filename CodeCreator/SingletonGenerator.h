#ifndef SINGLETONGENERATOR_H
#define SINGLETONGENERATOR_H

#include <QWidget>

class CodeGenerator;

namespace Ui {
class SingletonGenerator;
}

class SingletonGenerator : public QWidget
{
  Q_OBJECT

public:
  explicit SingletonGenerator(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~SingletonGenerator();

private:
  Ui::SingletonGenerator *ui;

  CodeGenerator* m_codeGenerator;
};

#endif // SINGLETONGENERATOR_H
