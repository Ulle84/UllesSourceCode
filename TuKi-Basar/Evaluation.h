#ifndef EVALUATION_H
#define EVALUATION_H

#include <QDialog>

namespace Ui {
class Evaluation;
}

class Evaluation : public QDialog
{
  Q_OBJECT

public:
  explicit Evaluation(QWidget *parent = 0);
  ~Evaluation();

private:
  Ui::Evaluation *ui;
};

#endif // EVALUATION_H
