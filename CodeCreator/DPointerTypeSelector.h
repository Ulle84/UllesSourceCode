#ifndef DPOINTERTYPESELECTOR_H
#define DPOINTERTYPESELECTOR_H

#include <QWidget>

#include "Class.h"

namespace Ui {
class DPointerTypeSelector;
}

class DPointerTypeSelector : public QWidget
{
  Q_OBJECT

public:
  explicit DPointerTypeSelector(QWidget *parent = 0);
  ~DPointerTypeSelector();

  Class::DPointerType dPointerType();
  bool setDPointerType(Class::DPointerType dPointerType);

  void setEnabled(bool enabled);

private:
  Ui::DPointerTypeSelector *ui;
};

#endif // DPOINTERTYPESELECTOR_H
