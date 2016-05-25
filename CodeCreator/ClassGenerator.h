#ifndef CLASSGENERATOR_H
#define CLASSGENERATOR_H

#include <QString>
#include <QStringList>

class ClassGenerator
{
public:

  ClassGenerator();

  QString createHeader();
  QString createImplementation();
  bool createFiles();

  void setClassName(const QString& className);
  void setNamespaceNames(const QStringList& namespaceNames);
  void setBaseClasses(const QStringList& baseClasses);
  void setIndent(const QString& indent);
  void setDeclareConstructorExplicit(bool declareConstructorExplicit);
  void setDeclareDestructorVirtual(bool declareDestructorVirtual);
  void setIncludeQObjectMacro(bool includeQObjectMacro);
  void setOutputDirectory(const QString& outputDirectory);
  void setOverwriteExistingFiles(bool overwriteExistingFiles);
  void setUppercaseHeaderGuard(bool uppercaseHeaderGuard);

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
  QString baseClassIncludes();
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

  enum FileType
  {
    Header,
    Source
  };
  bool createFile(FileType fileType);
  QString getSuffix(FileType fileType);

  QString m_className;
  QStringList m_namespaceNames;
  QStringList m_baseClasses;
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
};

#endif // CLASSGENERATOR_H
