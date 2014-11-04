#include <QApplication>
#include "ClipboardExtended.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ClipboardExtended w;
  w.show();
  
  return a.exec();
}
