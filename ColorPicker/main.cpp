#include <QApplication>
#include "ColorPicker.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  ColorPicker w;
  w.show();

  return a.exec();
}
