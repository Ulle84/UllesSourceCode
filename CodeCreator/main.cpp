#include <QApplication>
#include <QDebug>

#include "CodeCreator.h"
#include "Class.h"
#include "Function.h"
#include "Parameter.h"
#include "Interface.h"

int main(int argc, char* argv[])
{
  /*Parameter parameter("type", "name");
  qDebug() << parameter.toString();

  Parameter parameter2(" test my const type\t &name  =  \t0");
  qDebug() << parameter2.toString();

  Parameter parameter3("void myTest");
  qDebug() << parameter3.toString();

  Function function1("virtual void 2 myTest(int i, bool b, myType mt)=0;");
  qDebug() << function1.toString();

  Function function2("virtual void myTest( )=0;");
  qDebug() << function2.toString();*/

  QString interfaceDescription;
  interfaceDescription.append("virtual bool *myTest(int i, bool b, myType mt = nullptr)=0;");
  interfaceDescription.append("\nvirtual void myTest( )=0;");
  interfaceDescription.append("\nvoid myTest2(const QString& param);");
  interfaceDescription.append("\nvoid myTest2(const QString& param) = 0;");
  interfaceDescription.append("\n//void commented(const QString& param) = 0;");

  Interface interface(interfaceDescription);

  qDebug() << interface.toString();

  Class test;
  test.setClassName("Test");
  test.setDeclareDestructorVirtual(false);
  test.setDeclareConstructorExplicit(false);
  test.setIncludeQObjectMacro(false);
  test.setDestructorDeclarationType(Class::DeclarationType::Public);
  test.setConstructorDeclarationType(Class::DeclarationType::Public);
  test.setCopyConstructorDeclarationType(Class::DeclarationType::NoDeclaration);
  test.setCopyOperatorDeclarationType(Class::DeclarationType::NoDeclaration);
  test.setMoveConstructorDeclarationType(Class::DeclarationType::NoDeclaration);
  test.setMoveOperatorDeclarationType(Class::DeclarationType::NoDeclaration);
  test.setOutputDirectory("D:\\ube\\Misc\\UllesSourceCode\\CodeCreator\\");
  test.setOverwriteExistingFiles(true);
  //classGenerator.setSingletonType(ClassGenerator::SingletonType::Eager);

  QStringList baseClasses;
  baseClasses.append("BaseA");
  baseClasses.append("BaseB");
  //classGenerator.setBaseClasses(baseClasses);

  QStringList namespaces;
  namespaces.append("namespaceA");
  namespaces.append("namespaceB");
  //classGenerator.setNamespaceNames(namespaces);

  /*qDebug() << classGenerator.createHeader();
  qDebug() << "----------------------------------------------------";
  qDebug() << classGenerator.createImplementation();

  if (classGenerator.createFiles())
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
