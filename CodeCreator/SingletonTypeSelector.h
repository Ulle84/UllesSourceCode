#ifndef SINGLETONTYPESELECTOR_H
#define SINGLETONTYPESELECTOR_H

#include <QWidget>

#include "Class.h"

namespace Ui {
class SingletonTypeSelector;
}

class SingletonTypeSelector : public QWidget
{
  Q_OBJECT

public:
  explicit SingletonTypeSelector(QWidget *parent = 0);
  ~SingletonTypeSelector();

  Class::SingletonType singletonType();
  bool setSingletonType(Class::SingletonType singletonType);

  void setEnabled(bool enabled);

private:
  Ui::SingletonTypeSelector *ui;
};

#endif // SINGLETONTYPESELECTOR_H
