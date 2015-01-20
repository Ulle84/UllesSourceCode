#ifndef INTERFACEGENERATOR_H
#define INTERFACEGENERATOR_H

#include <QWidget>

namespace Ui {
class InterfaceGenerator;
}

class InterfaceGenerator : public QWidget
{
  Q_OBJECT
  
public:
  explicit InterfaceGenerator(QWidget *parent = 0);
  ~InterfaceGenerator();
  
private:
  Ui::InterfaceGenerator *ui;
};

#endif // INTERFACEGENERATOR_H
