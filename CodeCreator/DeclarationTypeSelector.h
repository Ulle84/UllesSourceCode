#ifndef DECLARATIONTYPESELECTOR_H
#define DECLARATIONTYPESELECTOR_H

#include <QMap>
#include <QString>
#include <QWidget>

#include "Class.h"

namespace Ui {
class DeclarationTypeSelector;
}

class DeclarationTypeSelector : public QWidget
{
  Q_OBJECT

public:
  explicit DeclarationTypeSelector(QWidget *parent = 0);
  ~DeclarationTypeSelector();

  Class::DeclarationType declarationType();
  bool setDeclarationType(Class::DeclarationType declarationType);

  void setEnabled(bool enabled);

private:
  Ui::DeclarationTypeSelector *ui;
};

#endif // DECLARATIONTYPESELECTOR_H
