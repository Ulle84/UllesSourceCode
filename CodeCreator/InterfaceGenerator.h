#ifndef INTERFACEGENERATOR_H
#define INTERFACEGENERATOR_H

#include <QWidget>

class CodeGenerator;

namespace Ui {
class InterfaceGenerator;
}

class InterfaceGenerator : public QWidget
{
  Q_OBJECT

public:
  explicit InterfaceGenerator(CodeGenerator* codeGenerator, QWidget *parent = 0);
  ~InterfaceGenerator();

private slots:
  void on_pushButtonStart_clicked();

private:
  Ui::InterfaceGenerator *ui;

  CodeGenerator* m_codeGenerator;
};

#endif // INTERFACEGENERATOR_H
