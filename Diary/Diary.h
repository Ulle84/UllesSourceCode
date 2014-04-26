#ifndef DIARY_H
#define DIARY_H

#include <QWidget>

namespace Ui
{
class Diary;
}

class Diary : public QWidget
{
  Q_OBJECT

public:
  explicit Diary(QWidget* parent = 0);
  ~Diary();

private slots:
  void on_pushButtonToday_clicked();

  void on_pushButtonOneDayBack_clicked();

  void on_pushButtonOneDayForward_clicked();

  void on_pushButtonOneMonthBack_clicked();

  void on_pushButtonOneMonthForward_clicked();

  void on_pushButtonOneYearBack_clicked();

  void on_pushButtonOneYearForward_clicked();

private:
  Ui::Diary* ui;
};

#endif // DIARY_H
