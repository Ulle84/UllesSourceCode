#include <QtGui/QApplication>
#include "clipboardextended.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  QCoreApplication::setOrganizationDomain("UllesSourceCodeDomain");
  QCoreApplication::setOrganizationName("UllesSourceCode");
  QCoreApplication::setApplicationName("ClipBoardExtended");
  QCoreApplication::setApplicationVersion("1.0.0");
  ClipboardExtended w;
  w.show();
  return a.exec();
}
