#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

private slots:
  void on_spinBox_valueChanged(int seconds);
  void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

private:
  void calculate();

  Ui::Widget *ui;
  QDateTime m_dateTime;
  int m_seconds;
};

#endif // WIDGET_H
