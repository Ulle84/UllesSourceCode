#ifndef DATETIMEADDER_H
#define DATETIMEADDER_H

#include <QWidget>
#include <QDateTime>

namespace Ui
{
class DateTimeAdder;
}

class DateTimeAdder : public QWidget
{
  Q_OBJECT

public:
  explicit DateTimeAdder(QWidget* parent = 0);
  ~DateTimeAdder();

private slots:
  void on_spinBox_valueChanged(int seconds);
  void on_dateTimeEdit_dateTimeChanged(const QDateTime& dateTime);

private:
  void calculate();

  Ui::DateTimeAdder* ui;
  QDateTime m_dateTime;
  int m_seconds;

};

#endif // DATETIMEADDER_H
