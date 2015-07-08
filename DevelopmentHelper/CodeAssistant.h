#ifndef CODEASSISTANT_H
#define CODEASSISTANT_H

#include <QWidget>

namespace Ui
{
class CodeAssistant;
}

class CodeAssistant : public QWidget
{
  Q_OBJECT

public:
  explicit CodeAssistant(QWidget* parent = 0);
  ~CodeAssistant();

private slots:


  void on_lineEditContainer_returnPressed();

  void on_lineEditForLoopIterator_returnPressed();

  void on_lineEditForLoopEnd_returnPressed();

private:
  void createForLoopCode();

  Ui::CodeAssistant* ui;
};

#endif // CODEASSISTANT_H
