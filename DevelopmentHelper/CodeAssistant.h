#ifndef CODEASSISTANT_H
#define CODEASSISTANT_H

#include <QWidget>

namespace Ui {
class CodeAssistant;
}

class CodeAssistant : public QWidget
{
  Q_OBJECT

public:
  explicit CodeAssistant(QWidget *parent = 0);
  ~CodeAssistant();

private slots:
  void on_lineEditContainer_returnPressed();
  void on_lineEditForLoop_returnPressed();

private:
  Ui::CodeAssistant *ui;
};

#endif // CODEASSISTANT_H
