#ifndef CLASSGENERATOR_H
#define CLASSGENERATOR_H

#include <QString>
#include <QStringList>

class ClassGenerator
{
public:


  ClassGenerator();

  struct Options
  {
    bool declareConstructorExplicit;
    bool declareDestructorVirtual;
    bool includeQObjectMacro;
  };
  QString createHeader(const Options& options);
  QString createImplementation(const Options& options);




  void setClassName(const QString& className);
  void setNamespaceNames(const QStringList& namespaceNames);
  void setBaseClasses(const QStringList& baseClasses);
  void setIndent(const QString& indent);

private:
  QString leadingWhitespace(bool indent);
  QString namespaceStart();
  QString namespaceEnd();
  QString headerGuardStart();
  QString headerGuardEnd();
  QString headerGuard();
  QString baseClassIncludes();
  QString section(const QString& sectionName);
  QString constructorDeclaration(const Options& options);
  QString constructorImplementation(const Options& options);
  QString destructorDeclaration(const Options& options);
  QString destructorImplementation(const Options& options);
  QString classDeclaration(const Options& options);
  QString include(const QString& header);


  QString m_className;
  QStringList m_namespaceNames;
  QStringList m_baseClasses;
  QString m_indent;
};

#endif // CLASSGENERATOR_H
