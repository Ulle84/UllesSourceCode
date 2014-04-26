#include <iostream>

#include <QtCore/QCoreApplication>
#include <QFile>
#include <QList>
#include <QStringList>
#include <QTextStream>
#include <QTimer>
#include <QVariant>

#include "deletefiles.h"

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);
  DeleteFiles deleteFiles("datFileTest.txt");
  //deleteFiles.checkFiles();
  QString datFileString = "datFileTest.txt"; //ToDo datFile aus argv


  //QTimer::singleShot(0, &app, SLOT(quit())); // this jumps out of event-loop and ends the Programm
  return app.exec();
}
