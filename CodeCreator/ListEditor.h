#ifndef LISTEDITOR_H
#define LISTEDITOR_H

#include <QWidget>

namespace Ui {
class ListEditor;
}

class ListEditor : public QWidget
{
  Q_OBJECT

public:
  explicit ListEditor(QWidget *parent = 0);
  ~ListEditor();

private:
  Ui::ListEditor *ui;
};

#endif // LISTEDITOR_H
