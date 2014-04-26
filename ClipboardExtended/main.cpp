#include <QtGui/QApplication>
#include "clipboardextended.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  ClipboardExtended w;
  w.resize(800, 600);
  w.show();
  return a.exec();
}
