#ifndef SELECTORDECLARATIONTYPE_H
#define SELECTORDECLARATIONTYPE_H

#include <QWidget>

#include "Class.h"

namespace Ui {
class SelectorDeclarationType;
}

class SelectorDeclarationType : public QWidget
{
  Q_OBJECT

public:
  explicit SelectorDeclarationType(QWidget *parent = 0);
  ~SelectorDeclarationType();

  Class::DeclarationType declarationType();
  bool setDeclarationType(Class::DeclarationType declarationType);

  void setEnabled(bool enabled);

private:
  Ui::SelectorDeclarationType *ui;
};

#endif // SELECTORDECLARATIONTYPE_H
