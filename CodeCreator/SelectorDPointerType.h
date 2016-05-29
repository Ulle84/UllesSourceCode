#ifndef SELECTORDPOINTERTYPE_H
#define SELECTORDPOINTERTYPE_H

#include <QWidget>

#include "Class.h"

namespace Ui {
class SelectorDPointerType;
}

class SelectorDPointerType : public QWidget
{
  Q_OBJECT

public:
  explicit SelectorDPointerType(QWidget *parent = 0);
  ~SelectorDPointerType();

  Class::DPointerType dPointerType();
  bool setDPointerType(Class::DPointerType dPointerType);

  void setEnabled(bool enabled);

signals:
  void dPointerTypeChanged(int dPointerType);

private slots:
  void on_comboBox_currentIndexChanged(int index);

private:
  Ui::SelectorDPointerType *ui;
};

#endif // SELECTORDPOINTERTYPE_H
