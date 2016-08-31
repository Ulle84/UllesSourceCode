#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;

  if (argc > 1)
  {
    w.setWorkingDirectory(argv[1]);
  }

  w.show();

  return a.exec();
}
