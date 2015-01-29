#include <QApplication>
#include "CodeHelper.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CodeHelper w;
  w.show();
  
  return a.exec();
}
