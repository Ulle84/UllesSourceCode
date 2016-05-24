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
  void setConstructorDeclarationType(DeclarationType constructorDeclarationType);
  void setDestructorDeclarationType(DeclarationType destructorDeclarationType);
  void setCopyConstructorDeclarationType(DeclarationType copyConstructorDeclarationType);
  void setCopyOperatorDeclarationType(DeclarationType copyOperatorDeclarationType);
  void setMoveConstructorDeclarationType(DeclarationType moveConstructorDeclarationType);
  void setMoveOperatorDeclarationType(DeclarationType moveOperatorDeclarationType);
  void setOutputDirectory(const QString& outputDirectory);
  void setOverwriteExistingFiles(bool overwriteExistingFiles);
  void setUppercaseHeaderGuard(bool uppercaseHeaderGuard);

private:
  QString leadingWhitespace(bool indent);
  QString namespaceStart();
  QString namespaceEnd();
  QString headerGuardStart();
  QString headerGuardEnd();
  QString headerGuard();
  QString baseClassIncludes();
  QString section(const QString& sectionName);
  QString classDeclaration();
  QString include(const QString& header);
  QString emptyBlock();
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

  enum FileType
  {
    HEADER,
    SOURCE
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
};

#endif // CLASSGENERATOR_H
