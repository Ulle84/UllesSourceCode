#include "CodeCleanerGui.h"
#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  CodeCleanerGui w;
  w.show();

  return a.exec();
}
