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

  ClassGenerator classGenerator;
  classGenerator.setClassName("MyClass");

  QStringList baseClasses;
  baseClasses.append("BaseA");
  baseClasses.append("BaseB");
  classGenerator.setBaseClasses(baseClasses);

  QStringList namespaces;
  namespaces.append("namespaceA");
  namespaces.append("namespaceB");
  //classGenerator.setNamespaceNames(namespaces);

  qDebug() << classGenerator.createHeader(options);
  qDebug() << classGenerator.createImplementation(options);

  return 0;

  QApplication a(argc, argv);

  CodeCreator w;
  w.show();
  
  return a.exec();
}
