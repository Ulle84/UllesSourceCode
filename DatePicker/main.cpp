#include <QApplication>
#include "datepicker.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  DatePicker w;
  w.show();

  return a.exec();
}
