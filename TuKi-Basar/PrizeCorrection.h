#ifndef PRIZECORRECTION_H
#define PRIZECORRECTION_H

#include <QDialog>

namespace Ui {
class PrizeCorrection;
}

class PrizeCorrection : public QDialog
{
  Q_OBJECT

public:
  explicit PrizeCorrection(QWidget *parent = 0);
  ~PrizeCorrection();
  void setPrize(double prize);
  double getPrize();

private:
  Ui::PrizeCorrection *ui;
};

#endif // PRIZECORRECTION_H
