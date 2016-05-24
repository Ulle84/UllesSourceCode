#include <QApplication>
#include <QDebug>

#include "CodeCreator.h"
#include "ClassGenerator.h"

int main(int argc, char* argv[])
{
  ClassGenerator classGenerator;
  classGenerator.setClassName("Test");
  classGenerator.setDeclareDestructorVirtual(false);
  classGenerator.setDeclareConstructorExplicit(false);
  classGenerator.setIncludeQObjectMacro(false);
  classGenerator.setDestructorDeclarationType(ClassGenerator::DeclarationType::PUBLIC);
  classGenerator.setConstructorDeclarationType(ClassGenerator::DeclarationType::PUBLIC);
  classGenerator.setCopyConstructorDeclarationType(ClassGenerator::DeclarationType::NONE);
  classGenerator.setCopyOperatorDeclarationType(ClassGenerator::DeclarationType::NONE);
  classGenerator.setMoveConstructorDeclarationType(ClassGenerator::DeclarationType::NONE);
  classGenerator.setMoveOperatorDeclarationType(ClassGenerator::DeclarationType::NONE);
  classGenerator.setOutputDirectory("D:\\ube\\Misc\\UllesSourceCode\\CodeCreator\\");
  classGenerator.setOverwriteExistingFiles(true);

  QStringList baseClasses;
  baseClasses.append("BaseA");
  baseClasses.append("BaseB");
  //classGenerator.setBaseClasses(baseClasses);

  QStringList namespaces;
  namespaces.append("namespaceA");
  namespaces.append("namespaceB");
  //classGenerator.setNamespaceNames(namespaces);

  qDebug() << classGenerator.createHeader();
  qDebug() << "----------------------------------------------------";
  qDebug() << classGenerator.createImplementation();

  /*if (classGenerator.createFiles(options))
    {
    qDebug() << "file succesfully writen";
    }
    else
    {
    qDebug() << "error while writing files";
    }*/

  return 0;

  QApplication a(argc, argv);

  CodeCreator w;
  w.show();

  return a.exec();
}
