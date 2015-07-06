#ifndef DATETIMEHELPER_H
#define DATETIMEHELPER_H

#include <QDate>
#include <QString>
#include <QWidget>

class QSettings;

namespace Ui {
class DateTimeHelper;
}

class DateTimeHelper : public QWidget
{
  Q_OBJECT

public:
  explicit DateTimeHelper(QWidget *parent = 0);
  ~DateTimeHelper();

private slots:
  void on_calendarWidget_clicked(const QDate& date);
  void on_pushButtonToday_clicked();
  void on_pushButtonDefault_clicked();
  void on_lineEditOutputFormat_textChanged(const QString& newOutputFormat);

private:
  void copyDateToClipboard();

  Ui::DateTimeHelper *ui;

  QString m_outputFormat;
  const QString m_outputFormatDefault;
  QSettings* m_settings;
};

#endif // DATETIMEHELPER_H
