#ifndef DATEPICKER_H
#define DATEPICKER_H

#include <QWidget>
#include <QDate>
#include <QString>

namespace Ui
{
class DatePicker;
}

class DatePicker : public QWidget
{
  Q_OBJECT

private:
  QString outputFormat;
  QString outputFormatDefault;

public:
  explicit DatePicker(QWidget* parent = 0);
  ~DatePicker();

private slots:
  void on_calendarWidget_clicked(const QDate& date);

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_lineEdit_textChanged(const QString& newOutputFormat);

  void on_pushButton_3_clicked();

private:
  Ui::DatePicker* ui;
};

#endif // DATEPICKER_H
