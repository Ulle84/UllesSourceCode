#include "DevelopmentHelper.h"
#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  DevelopmentHelper w;
  w.show();

  return a.exec();
}
