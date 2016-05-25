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
  classGenerator.setDestructorDeclarationType(ClassGenerator::DeclarationType::Public);
  classGenerator.setConstructorDeclarationType(ClassGenerator::DeclarationType::Public);
  classGenerator.setCopyConstructorDeclarationType(ClassGenerator::DeclarationType::NoDeclaration);
  classGenerator.setCopyOperatorDeclarationType(ClassGenerator::DeclarationType::NoDeclaration);
  classGenerator.setMoveConstructorDeclarationType(ClassGenerator::DeclarationType::NoDeclaration);
  classGenerator.setMoveOperatorDeclarationType(ClassGenerator::DeclarationType::NoDeclaration);
  classGenerator.setOutputDirectory("D:\\ube\\Misc\\UllesSourceCode\\CodeCreator\\");
  classGenerator.setOverwriteExistingFiles(true);
  //classGenerator.setSingletonType(ClassGenerator::SingletonType::Eager);

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

  if (classGenerator.createFiles())
  {
    qDebug() << "file succesfully writen";
  }
  else
  {
    qDebug() << "error while writing files";
  }

  return 0;

  QApplication a(argc, argv);

  CodeCreator w;
  w.show();

  return a.exec();
}
