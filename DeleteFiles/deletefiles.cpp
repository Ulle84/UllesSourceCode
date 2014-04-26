#include "deletefiles.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QTimer>
#include <QObject>
#include <QVariant>

DeleteFiles::DeleteFiles(QString string)
{
  datFileString = string;
  init();

  QTimer* timer = new QTimer();
  timer->start(2000);
  connect(timer, SIGNAL(timeout()), this, SLOT(checkFiles()));
}

bool DeleteFiles::checkFiles()
{
  std::cout << "checkFiles" << std::endl;
  return true;
}

bool DeleteFiles::init()
{
  QFile* datFile = new QFile(datFileString);

  if (!datFile->open(QIODevice::ReadOnly | QIODevice::Text))
  {
    return false;
  }

  QTextStream in(datFile);
  QString tempString;
  QStringList tempStringList;

  while (!in.atEnd())
  {
    tempString = in.readLine();
    tempStringList = tempString.split(" ");

    if (tempStringList.length() == 2)
    {
      numbers.append(QVariant(tempStringList[0]).toInt());
      directories.append(tempStringList[1]);
    }
  }
}
