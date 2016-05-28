#ifndef SELECTORSINGLETONTYPE_H
#define SELECTORSINGLETONTYPE_H

#include <QWidget>

#include "Class.h"

namespace Ui {
class SelectorSingletonType;
}

class SelectorSingletonType : public QWidget
{
  Q_OBJECT

public:
  explicit SelectorSingletonType(QWidget *parent = 0);
  ~SelectorSingletonType();

  Class::SingletonType singletonType();
  bool setSingletonType(Class::SingletonType singletonType);

  void setEnabled(bool enabled);

private:
  Ui::SelectorSingletonType *ui;
};

#endif // SELECTORSINGLETONTYPE_H
