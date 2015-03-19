#include <QDate>

#include "SuperUser.h"

QString SuperUser::password()
{
  QDate today = QDate::currentDate();

  // extract data
  int day   = today.day();
  int month = today.month();
  int year  = today.year() % 100;

  // calculate cross sum
  int sum = 0;
  sum += day   / 10;
  sum += day   % 10;
  sum += month / 10;
  sum += month % 10;
  sum += year  / 10;
  sum += year  % 10;

  return QString("%1%2%3%4%5")
         .arg((day   + sum) % 100)
         .arg((71    + sum) % 100)
         .arg((month + sum) % 100)
         .arg((52    + sum) % 100)
         .arg((year  + sum) % 100);
}
