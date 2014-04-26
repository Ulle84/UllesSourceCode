#ifndef DELETEFILES_H
#define DELETEFILES_H

#include <QList>
#include <QObject>
#include <QString>
#include <QTimer>

#include <iostream>

class DeleteFiles : QObject
{
  Q_OBJECT

private:
  QString datFileString;
  QList<QString> directories;
  QList<int> numbers;

public:
  DeleteFiles(QString string);
  bool init();

public slots:
  bool checkFiles();
};

#endif // DELETEFILES_H
