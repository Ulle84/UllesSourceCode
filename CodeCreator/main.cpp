#include <QApplication>
#include <QDebug>
#include "CodeCreator.h"

#include "ClassGenerator.h"

int main(int argc, char *argv[])
{
  ClassGenerator::Options options;
  options.declareDestructorVirtual = false;
  options.declareConstructorExplicit = false;
  options.includeQObjectMacro = false;
  options.declareConstrucorPrivate = true;
  options.copyConstructor = ClassGenerator::DeclarationType::PRIVATE;
  options.copyOperator = ClassGenerator::DeclarationType::PRIVATE;
  options.outputDirectory = "D:\\ube\\Misc\\UllesSourceCode\\CodeCreator\\";
  options.overwriteExistingFiles = true;

  ClassGenerator classGenerator;
  classGenerator.setClassName("Test");

  QStringList baseClasses;
  //baseClasses.append("BaseA");
  //baseClasses.append("BaseB");
  classGenerator.setBaseClasses(baseClasses);

  QStringList namespaces;
  namespaces.append("namespaceA");
  namespaces.append("namespaceB");
  //classGenerator.setNamespaceNames(namespaces);

  qDebug() << classGenerator.createHeader(options);
  qDebug() << "----------------------------------------------------";
  qDebug() << classGenerator.createImplementation(options);

  if(classGenerator.createFiles(options))
  {
    qDebug() << "file succesfully writen";
  }
  else
    qDebug() << "error while writing files";

  return 0;

  QApplication a(argc, argv);

  CodeCreator w;
  w.show();
  
  return a.exec();
}
