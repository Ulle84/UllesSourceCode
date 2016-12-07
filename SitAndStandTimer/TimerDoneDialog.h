#ifndef TIMERDONEDIALOG_H
#define TIMERDONEDIALOG_H

#include <QDialog>

namespace Ui {
class TimerDoneDialog;
}

class TimerDoneDialog : public QDialog
{
  Q_OBJECT

public:
  explicit TimerDoneDialog(QWidget *parent = 0);
  ~TimerDoneDialog();

private:
  Ui::TimerDoneDialog *ui;
};

#endif // TIMERDONEDIALOG_H
