#ifndef SINGLETONGENERATOR_H
#define SINGLETONGENERATOR_H

#include <QWidget>

namespace Ui {
class SingletonGenerator;
}

class SingletonGenerator : public QWidget
{
  Q_OBJECT
  
public:
  explicit SingletonGenerator(QWidget *parent = 0);
  ~SingletonGenerator();
  
private:
  Ui::SingletonGenerator *ui;
};

#endif // SINGLETONGENERATOR_H
