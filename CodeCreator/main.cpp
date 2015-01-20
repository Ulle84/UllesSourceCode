#include <QApplication>
#include "CodeCreator.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CodeCreator w;
  w.show();
  
  return a.exec();
}
