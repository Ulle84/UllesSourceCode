#ifndef CODEHELPER_H
#define CODEHELPER_H

#include <QWidget>

namespace Ui {
class CodeHelper;
}

class CodeHelper : public QWidget
{
  Q_OBJECT

public:
  explicit CodeHelper(QWidget *parent = 0);
  ~CodeHelper();

private slots:
  void on_lineEditContainer_editingFinished();

private:
  Ui::CodeHelper *ui;
};

#endif // CODEHELPER_H
