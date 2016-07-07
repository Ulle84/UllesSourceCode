#include <QApplication>
#include <QDebug>

#include "CodeCreator.h"
#include "Class.h"
//#include "Function.h"
#include "Parameter.h"
#include "Interface.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  CodeCreator w;
  w.show();

  return a.exec();
}
