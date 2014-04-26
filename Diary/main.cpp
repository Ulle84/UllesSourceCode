#include <QApplication>
#include "Diary.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  Diary w;
  w.show();

  return a.exec();
}
