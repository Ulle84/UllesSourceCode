#include <QApplication>
#include "FileOrDirSelector.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  FileOrDirSelector w;
  w.show();

  return a.exec();
}
