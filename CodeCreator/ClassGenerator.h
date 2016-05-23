#ifndef CLASSGENERATOR_H
#define CLASSGENERATOR_H

#include <QString>
#include <QStringList>

class ClassGenerator
{
public:


  ClassGenerator();

  enum DeclarationType
  {
    NONE,
    PUBLIC,
    PRIVATE
  };

  struct Options
  {
    Options();

    bool declareConstructorExplicit;
    bool declareDestructorVirtual;
    bool includeQObjectMacro;
    DeclarationType copyConstructor;
    DeclarationType copyOperator;
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
  QString classDeclaration(const Options& options);
  QString include(const QString& header);
  QString emptyBlock();
  QString constRef();

  QString constructorDeclaration(const Options& options);
  QString constructorImplementation(const Options& options);

  QString copyConstructorDeclaration(const Options& options);
  QString copyConstructorImplementation(const Options& options);

  QString copyOperatorDeclaration(const Options& options);
  QString copyOperatorImplementation(const Options& options);



  QString destructorDeclaration(const Options& options);
  QString destructorImplementation(const Options& options);


  QString m_className;
  QStringList m_namespaceNames;
  QStringList m_baseClasses;
  QString m_indent;
};

#endif // CLASSGENERATOR_H
