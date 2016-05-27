#ifndef CLASS_H
#define CLASS_H

#include <QString>
#include <QStringList>

#include "Interface.h"
#include "Method.h"

class Class
{
public:
  Class(const QString& name);

  QString name() const;

  QString createHeader();
  QString createImplementation();
  bool createFiles();
  bool createHeaderFile();
  bool createImplementationFile();

  void setClassName(const QString& className);
  void setNamespaceNames(const QStringList& namespaceNames);
  void setBaseClass(const Class* baseClass);
  void setInterfaces(const QList<Interface>& interfaces);
  void setIndent(const QString& indent);
  void setDeclareConstructorExplicit(bool declareConstructorExplicit);
  void setDeclareDestructorVirtual(bool declareDestructorVirtual);
  void setIncludeQObjectMacro(bool includeQObjectMacro);
  void setOutputDirectory(const QString& outputDirectory);
  void setOverwriteExistingFiles(bool overwriteExistingFiles);
  void setUppercaseHeaderGuard(bool uppercaseHeaderGuard);
  void setMethods(const QList<Method>& methods);

  enum DeclarationType
  {
    NoDeclaration,
    Public,
    Private
  };
  void setConstructorDeclarationType(DeclarationType constructorDeclarationType);
  void setDestructorDeclarationType(DeclarationType destructorDeclarationType);
  void setCopyConstructorDeclarationType(DeclarationType copyConstructorDeclarationType);
  void setCopyOperatorDeclarationType(DeclarationType copyOperatorDeclarationType);
  void setMoveConstructorDeclarationType(DeclarationType moveConstructorDeclarationType);
  void setMoveOperatorDeclarationType(DeclarationType moveOperatorDeclarationType);

  enum SingletonType
  {
    NoSingleton,
    Eager,
    LazyProtectedWithQMutex // TODO implement this option
  };
  void setSingletonType(SingletonType singletonType);

  enum DPointerType
  {
    NoDPointer,
    DPointer
    //DPointerWithQPointer,
    //InheritableDPointer
  };
  void setDPointerType(DPointerType dPointerType);

private:
  void checkOptions();

  void append(QString& code, unsigned int indent, const QString& toAppend);
  void appendLine(QString& code, unsigned int indent, const QString& toAppend);

  QString leadingWhitespace(unsigned int indent = 0);
  QString namespaceStart();
  QString namespaceEnd();
  QString headerGuardStart();
  QString headerGuardEnd();
  QString headerGuard();
  QString includes();
  QString section(const QString& sectionName);
  QString classDeclaration();
  QString include(const QString& headerName, bool useSuffix, bool useAngleBrackets);
  QString emptyBlock(unsigned int indent = 0);
  QString openBlock(unsigned int indent = 0);
  QString closeBlock(unsigned int indent = 0);
  QString constRef();
  QString moveRef();
  QString toDo(const QString& task);
  QString toDoImplementation();

  QString constructorDeclaration();
  QString constructorImplementation();

  QString copyConstructorDeclaration();
  QString copyConstructorImplementation();

  QString moveConstructorDeclaration();
  QString moveConstructorImplementation();

  QString copyOperatorDeclaration();
  QString copyOperatorImplementation();

  QString moveOperatorDeclaration();
  QString moveOperatorImplementation();

  QString destructorDeclaration();
  QString destructorImplementation();

  QString singletonInstance();
  QString singletonInitialization();
  QString singletonGetInstanceDeclaration();
  QString singletonGetInstanceImplementation();

  QString dPointerClass();
  QString dPointerDeclaration();
  QString dPointerImplementation();
  QString dPointerInitialization(bool copyRhs);

  bool hasMethodDeclarations(Method::DeclarationType declarationType);
  QString methodDeclarations(Method::DeclarationType declarationType);

  enum FileType
  {
    Header,
    Source
  };
  bool createFile(FileType fileType);
  QString getSuffix(FileType fileType);

  QString m_name;
  QStringList m_namespaceNames;
  const Class* m_baseClass;
  QList<Interface> m_interfaces;
  QString m_indent;

  bool m_declareConstructorExplicit;
  bool m_declareDestructorVirtual;
  bool m_includeQObjectMacro;
  DeclarationType m_constructorDeclarationType;
  DeclarationType m_destructorDeclarationType;
  DeclarationType m_copyConstructorDeclarationType;
  DeclarationType m_copyOperatorDeclarationType;
  DeclarationType m_moveConstructorDeclarationType;
  DeclarationType m_moveOperatorDeclarationType;
  QString m_outputDirectory;
  bool m_overwriteExistingFiles;
  bool m_uppercaseHeaderGuard;
  SingletonType m_singletonType;
  DPointerType m_dPointerType;
  QList<Method> m_methods;
  QString m_dPointerSuffix;
  QString m_dPointerName;
  QString m_rhs;
  QString m_memberPrefix;
  bool m_sectionEmtpy;
};

#endif // CLASS_H
