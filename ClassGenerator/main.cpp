#include <QApplication>
#include "ClassGenerator.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ClassGenerator w;
  w.show();
  
  return a.exec();
}
