#ifndef DOUBLEBUTTON_H
#define DOUBLEBUTTON_H

#include <QWidget>

namespace Ui {
class DoubleButton;
}

class DoubleButton : public QWidget
{
  Q_OBJECT

public:
  explicit DoubleButton(QWidget *parent = 0);
  ~DoubleButton();

  QString buttonText1();
  QString buttonText2();

  void setButtonText1(const QString& buttonText1);
  void setButtonText2(const QString& buttonText2);

private slots:
  void on_pushButton1_clicked();
  void on_pushButton2_clicked();

private:
  Ui::DoubleButton *ui;
};

#endif // DOUBLEBUTTON_H
