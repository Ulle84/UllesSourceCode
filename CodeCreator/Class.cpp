#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "Class.h"

Class::Class(const QString& name)
  : m_name(name),
    m_indent("  "),
    m_declareConstructorExplicit(false),
    m_declareDestructorVirtual(false),
    m_includeQObjectMacro(false),
    m_constructorDeclarationType(DeclarationType::Public),
    m_destructorDeclarationType(DeclarationType::Public),
    m_copyConstructorDeclarationType(DeclarationType::NoDeclaration),
    m_copyOperatorDeclarationType(DeclarationType::NoDeclaration),
    m_moveConstructorDeclarationType(DeclarationType::NoDeclaration),
    m_moveOperatorDeclarationType(DeclarationType::NoDeclaration),
    m_overwriteExistingFiles(false),
    m_uppercaseHeaderGuard(false),
    m_singletonType(SingletonType::NoSingleton),
    m_dPointerSuffix("P"),
    m_dPointerName("p"),
    m_rhs("rhs"),
    m_baseClass(0),
    m_memberPrefix("m_"),
    m_dPointerType(DPointerType::NoDPointer)
{
}

QString Class::name() const
{
  return m_name;
}

QString Class::createHeader()
{
  checkOptions();

  QString code;

  code.append(headerGuardStart());

  if (m_singletonType == SingletonType::LazyProtectedWithQMutex)
  {
    code.append(include("QtCore\\QMutex", false, true));
    code.append("\n");
  }

  code.append(includes());
  code.append(namespaceStart());
  code.append(classDeclaration());

  if (m_includeQObjectMacro)
  {
    appendLine(code, 1, "Q_OBJECT\n");
  }

  code.append(section("public"));

  if (m_singletonType != SingletonType::NoSingleton)
  {
    code.append(singletonGetInstanceDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_constructorDeclarationType == DeclarationType::Public)
  {
    code.append(constructorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_copyConstructorDeclarationType == DeclarationType::Public)
  {
    code.append(copyConstructorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_moveConstructorDeclarationType == DeclarationType::Public)
  {
    code.append(moveConstructorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_copyOperatorDeclarationType == DeclarationType::Public)
  {
    code.append(copyOperatorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_moveOperatorDeclarationType == DeclarationType::Public)
  {
    code.append(moveOperatorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_destructorDeclarationType == DeclarationType::Public)
  {
    code.append(destructorDeclaration());
    m_sectionEmtpy = false;
  }

  if (hasMethodDeclarations(Method::DeclarationType::Public))
  {
    if (!m_sectionEmtpy)
    {
      code.append("\n");
    }

    code.append(methodDeclarations(Method::DeclarationType::Public));
    m_sectionEmtpy = false;
  }

  if (hasInterfaceToImplement())
  {
    if (!m_sectionEmtpy)
    {
      code.append("\n");
    }
    code.append(interfaceDeclarations());

    m_sectionEmtpy = false;
  }

  if (m_constructorDeclarationType == DeclarationType::Private
      || m_copyConstructorDeclarationType == DeclarationType::Private
      || m_copyOperatorDeclarationType == DeclarationType::Private
      || m_moveConstructorDeclarationType == DeclarationType::Private
      || m_moveOperatorDeclarationType == DeclarationType::Private
      || m_destructorDeclarationType == DeclarationType::Private
      || m_singletonType != SingletonType::NoSingleton
      || m_dPointerType != DPointerType::NoDPointer)
  {
    code.append("\n");
    code.append(section("private"));
  }

  if (m_constructorDeclarationType == DeclarationType::Private)
  {
    code.append(constructorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_copyConstructorDeclarationType == DeclarationType::Private)
  {
    code.append(copyConstructorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_moveConstructorDeclarationType == DeclarationType::Private)
  {
    code.append(moveConstructorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_copyOperatorDeclarationType == DeclarationType::Private)
  {
    code.append(copyOperatorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_moveOperatorDeclarationType == DeclarationType::Private)
  {
    code.append(moveOperatorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_destructorDeclarationType == DeclarationType::Private)
  {
    code.append(destructorDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_dPointerType != DPointerType::NoDPointer)
  {
    if (!m_sectionEmtpy)
    {
      code.append("\n");
    }

    code.append(dPointerDeclaration());
    m_sectionEmtpy = false;
  }

  if (m_singletonType != SingletonType::NoSingleton)
  {
    if (!m_sectionEmtpy)
    {
      code.append("\n");
    }

   if (m_singletonType == SingletonType::LazyProtectedWithQMutex)
    {
      code.append(leadingWhitespace(1));
      code.append("static QMutex ");
      code.append(m_memberPrefix);
      code.append("mutex;\n");
    }

    code.append(singletonInstance());
    m_sectionEmtpy = false;
  }

  appendLine(code, 0, "};");

  code.append(namespaceEnd());
  code.append(headerGuardEnd());

  return code;
}

QString Class::createImplementation()
{
  checkOptions();

  QString code;

  code.append(include(m_name, true, false));
  code.append("\n");

  code.append(namespaceStart());

  bool alreadyOneImplementationPresent = false;

  if (m_dPointerType != DPointerType::NoDPointer)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }

    code.append(dPointerImplementation());

    alreadyOneImplementationPresent = true;
  }

  if (m_singletonType != SingletonType::NoSingleton)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }

    code.append(singletonInitialization());
    code.append("\n");
    code.append(singletonGetInstanceImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_constructorDeclarationType == DeclarationType::Public)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }

    code.append(constructorImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_copyConstructorDeclarationType == DeclarationType::Public)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }

    code.append(copyConstructorImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_moveConstructorDeclarationType == DeclarationType::Public)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }

    code.append(moveConstructorImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_copyOperatorDeclarationType == DeclarationType::Public)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }

    code.append(copyOperatorImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_moveOperatorDeclarationType == DeclarationType::Public)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }

    code.append(moveOperatorImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_destructorDeclarationType == DeclarationType::Public && !m_declareDestructorVirtual)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }

    code.append(destructorImplementation());
    alreadyOneImplementationPresent = true;
  }

  code.append(namespaceEnd());

  return code;
}

bool Class::createFiles()
{
  if (!createHeaderFile())
  {
    return false;
  }

  if (!createImplementationFile())
  {
    return false;
  }

  return true;
}

bool Class::createHeaderFile()
{
  return createFile(FileType::Header);
}

bool Class::createImplementationFile()
{
  return createFile(FileType::Source);
}

QString Class::constructorDeclaration()
{
  QString code = leadingWhitespace(1);

  if (m_declareConstructorExplicit)
  {
    code.append("explicit ");
  }

  code.append(m_name);
  code.append("()");

  if (m_singletonType != SingletonType::NoSingleton)
  {
    code.append("{}");
  }
  else
  {
    code.append(";");
  }

  code.append("\n");

  return code;
}

QString Class::constructorImplementation()
{
  QString code = leadingWhitespace(0);

  code.append(m_name);
  code.append("::");
  code.append(m_name);
  code.append("()\n");

  if (m_dPointerType != DPointerType::NoDPointer)
  {
    code.append(dPointerInitialization(false));
  }

  code.append(emptyBlock());

  return code;
}

QString Class::copyConstructorDeclaration()
{
  if (m_copyConstructorDeclarationType == DeclarationType::NoDeclaration)
  {
    return QString();
  }

  QString code = leadingWhitespace(1);

  code.append(m_name);
  code.append(constRef());

  if (m_copyConstructorDeclarationType == DeclarationType::Private)
  {
    code.append("{}");
  }
  else
  {
    code.append(";");
  }

  code.append("\n");

  return code;
}

QString Class::copyConstructorImplementation()
{
  QString code = leadingWhitespace(0);

  code.append(m_name);
  code.append("::");
  code.append(m_name);
  code.append(constRef());
  code.append("\n");

  if (m_dPointerType != DPointerType::NoDPointer)
  {
    code.append(dPointerInitialization(true));
  }

  code.append(emptyBlock());

  return code;
}

QString Class::moveConstructorDeclaration()
{
  if (m_moveConstructorDeclarationType == DeclarationType::NoDeclaration)
  {
    return QString();
  }

  QString code = leadingWhitespace(1);

  code.append(m_name);
  code.append(moveRef());

  if (m_copyConstructorDeclarationType == DeclarationType::Private)
  {
    code.append("{}");
  }
  else
  {
    code.append(";");
  }

  code.append("\n");

  return code;
}

QString Class::moveConstructorImplementation()
{
  QString code = leadingWhitespace(0);

  code.append(m_name);
  code.append("::");
  code.append(m_name);
  code.append(moveRef());
  code.append("\n");
  code.append(emptyBlock());

  return code;
}

QString Class::copyOperatorDeclaration()
{
  if (m_copyOperatorDeclarationType == DeclarationType::NoDeclaration)
  {
    return QString();
  }

  QString code = leadingWhitespace(1);

  code.append(m_name);
  code.append("& operator= ");
  code.append(constRef());

  if (m_copyOperatorDeclarationType == DeclarationType::Private)
  {
    code.append("{}");
  }
  else
  {
    code.append(";");
  }

  code.append("\n");

  return code;
}

QString Class::copyOperatorImplementation()
{
  QString code = leadingWhitespace(0);

  code.append(m_name);
  code.append("& ");
  code.append(m_name);
  code.append("::operator=");
  code.append(constRef());
  code.append("\n");
  code.append(openBlock(0));
  append(code, 1, "if (this != &");
  code.append(m_rhs);
  code.append(")\n");
  code.append(openBlock(1));

  if (m_dPointerType != DPointerType::NoDPointer)
  {
    append(code, 2, "*");
    code.append(m_dPointerName);
    code.append(" = *(");
    code.append(m_rhs);
    code.append(".");
    code.append(m_dPointerName);
    code.append(");\n");
  }
  else
  {
    code.append(toDoImplementation(1));
  }

  code.append(closeBlock(1));

  appendLine(code, 1, "return *this;");
  code.append(closeBlock(0));

  return code;
}

QString Class::moveOperatorDeclaration()
{
  if (m_moveOperatorDeclarationType == DeclarationType::NoDeclaration)
  {
    return QString();
  }

  QString code = leadingWhitespace(1);

  code.append(m_name);
  code.append("& operator= ");
  code.append(moveRef());

  if (m_copyOperatorDeclarationType == DeclarationType::Private)
  {
    code.append("{}");
  }
  else
  {
    code.append(";");
  }

  code.append("\n");

  return code;
}

QString Class::moveOperatorImplementation()
{
  QString code = leadingWhitespace(0);

  code.append(m_name);
  code.append("& ");
  code.append(m_name);
  code.append("::operator=");
  code.append(moveRef());
  code.append("\n");
  code.append(openBlock());
  code.append(toDoImplementation());
  code.append(closeBlock());

  return code;
}

QString Class::destructorDeclaration()
{
  QString code = leadingWhitespace(1);

  if (m_declareDestructorVirtual)
  {
    code.append("virtual ");
  }

  code.append("~");
  code.append(m_name);
  code.append("()");

  if (m_declareDestructorVirtual || m_destructorDeclarationType == DeclarationType::Private)
  {
    code.append("{}");
  }
  else
  {
    code.append(";");
  }

  code.append("\n");

  return code;
}

QString Class::destructorImplementation()
{
  QString code = leadingWhitespace(0);

  code.append(m_name);
  code.append("::~");
  code.append(m_name);
  code.append("()\n");
  code.append(openBlock());

  if (m_dPointerType != DPointerType::NoDPointer)
  {
    append(code, 1, "delete ");
    code.append(m_dPointerName);
    code.append(";\n");
  }

  code.append(closeBlock());

  return code;
}

QString Class::singletonInstance()
{
  QString code = leadingWhitespace(1);

  code.append("static ");
  code.append(m_name);
  code.append("* ");
  code.append(m_memberPrefix);
  code.append("instance;\n");

  return code;
}

QString Class::singletonInitialization()
{
  QString code = leadingWhitespace(0);

  code.append(m_name);
  code.append("* ");
  code.append(m_name);
  code.append("::");
  code.append(m_memberPrefix);
  code.append("instance = ");

  if (m_singletonType == SingletonType::Eager)
  {
    code.append("new ");
    code.append(m_name);
    code.append("()");
  }
  else
  {
    code.append("nullptr");
  }

  code.append(";\n");

  return code;
}

QString Class::singletonGetInstanceDeclaration()
{
  QString code = leadingWhitespace(1);

  code.append("static ");
  code.append(m_name);
  code.append("* getInstance();\n");

  return code;
}

QString Class::singletonGetInstanceImplementation()
{
  QString code = leadingWhitespace(0);

  code.append(m_name);
  code.append("* ");
  code.append(m_name);
  code.append("::getInstance()\n");
  code.append(openBlock());

  if (m_singletonType == LazyProtectedWithQMutex)
  {
    append(code, 1, m_memberPrefix);
    code.append("mutex.lock();\n\n");
    append(code, 1, "if (");
    code.append(m_memberPrefix);
    code.append("instance == nullptr)\n");
    code.append(openBlock(1));
    append(code, 2, m_memberPrefix);
    code.append("instance = new ");
    code.append(m_name);
    code.append("();\n");
    code.append(closeBlock(1));
    code.append("\n");
    append(code, 1, m_memberPrefix);
    code.append("mutex.unlock();\n\n");
  }

  append(code, 1, "return ");
  code.append(m_memberPrefix);
  code.append("instance;\n");
  code.append(closeBlock());

  return code;
}

QString Class::dPointerClass()
{
  QString code;

  code.append(m_name);
  code.append(m_dPointerSuffix);

  return code;
}

QString Class::dPointerDeclaration()
{
  QString code;

  append(code, 1, "class ");
  code.append(dPointerClass());
  code.append(";\n");
  append(code, 1, dPointerClass());
  code.append("* ");
  code.append(m_dPointerName);
  code.append(";\n");

  return code;
}

QString Class::dPointerImplementation()
{
  QString code;

  append(code, 0, "class ");
  code.append(m_name);
  code.append("::");
  code.append(dPointerClass());
  code.append("\n");
  code.append(openBlock(0));
  code.append(section("public"));
  append(code, 0, toDoImplementation());
  append(code, 0, "};\n");

  return code;

}

QString Class::dPointerInitialization(bool copyRhs)
{
  QString code;

  append(code, 1, ": ");
  code.append(m_dPointerName);
  code.append("(new ");
  code.append(dPointerClass());
  code.append("(");
  if (copyRhs)
  {
    code.append("*");
    code.append(m_rhs);
    code.append(".");
    code.append(m_dPointerName);
  }
  code.append("))\n");

  return code;
}

QString Class::interfaceDeclarations()
{
  QString code;

  for (auto it = m_interfaces.begin(); it != m_interfaces.end(); it++)
  {
    if (!it->isToImplement())
    {
      continue;
    }

    append(code, 1, "// implementation of interface ");
    code.append(it->name());
    code.append("\n");

    for (auto it2 = it->begin(); it2 != it->end(); it2++)
    {
      append(code, 1, it2->declaration(true));
    }
  }

  return code;
}

bool Class::hasMethodDeclarations(Method::DeclarationType declarationType)
{
  for (auto it = m_methods.begin(); it != m_methods.end(); it++)
  {
    if (it->declarationType() == declarationType)
    {
      return true;
    }
  }

  return false;
}

QString Class::methodDeclarations(Method::DeclarationType declarationType)
{
  QString code;

  for (auto it = m_methods.begin(); it != m_methods.end(); it++)
  {
    if (it->declarationType() == declarationType)
    {
      appendLine(code, 1, it->declaration());
    }
  }

  return code;
}

bool Class::hasInterfaceToImplement()
{
  if (m_interfaces.isEmpty())
  {
    return false;
  }

  for (auto it = m_interfaces.begin(); it != m_interfaces.end(); it++)
  {
    if (it->isToImplement())
    {
      return true;
    }
  }

  return false;
}

bool Class::createFile(FileType fileType)
{
  QString suffix = getSuffix(fileType);

  QString fileName = m_outputDirectory + m_name + suffix;

  QFile file(fileName);

  if (file.exists() && !m_overwriteExistingFiles)
  {
    return false;
  }

  if (!file.open(QIODevice::WriteOnly))
  {
    return false;
  }

  QTextStream textStream(&file);

  if (fileType == FileType::Header)
  {
    textStream << createHeader();
  }
  else if (fileType == FileType::Source)
  {
    textStream << createImplementation();
  }

  file.close();

  return true;
}

QString Class::getSuffix(Class::FileType fileType)
{
  QString suffix;

  switch (fileType)
  {
  case FileType::Header:
    suffix = ".h";
    break;

  case FileType::Source:
    suffix = ".cpp";
    break;

  default:
    suffix = ".h";
  }

  return suffix;
}

QString Class::classDeclaration()
{
  QString code = leadingWhitespace(0);

  code.append("class ");
  code.append(m_name);

  if (m_baseClass != 0 || !m_interfaces.isEmpty())
  {
    code.append(" : ");

    if (m_baseClass != 0)
    {
      code.append("public ");
      code.append(m_baseClass->name());
    }

    for (auto it = m_interfaces.begin(); it != m_interfaces.end(); it++)
    {
      if (it != m_interfaces.begin() || m_baseClass != 0)
      {
        code.append(", ");
      }

      code.append("public ");
      code.append(it->name());
    }
  }

  code.append("\n");
  code.append(leadingWhitespace(0));
  code.append("{\n");

  return code;
}

QString Class::include(const QString& headerName, bool useSuffix, bool useAngleBrackets)
{
  QString code;

  code.append("#include ");
  code.append(useAngleBrackets ? "<" : "\"");
  code.append(headerName);

  if (useSuffix)
  {
    code.append(".h");
  }

  code.append(useAngleBrackets ? ">" : "\"");
  code.append("\n");

  return code;
}

QString Class::emptyBlock(unsigned int indent)
{
  QString code;

  code.append(openBlock(indent));
  code.append("\n");
  code.append(closeBlock(indent));

  return code;
}

QString Class::openBlock(unsigned int indent)
{
  QString code;

  appendLine(code, indent, "{");

  return code;
}

QString Class::closeBlock(unsigned int indent)
{
  QString code;

  appendLine(code, indent, "}");

  return code;
}

QString Class::constRef()
{
  QString code;

  code.append("(const ");
  code.append(m_name);
  code.append("& ");
  code.append(m_rhs);
  code.append(")");

  return code;
}

QString Class::moveRef()
{
  QString code;

  code.append("(");
  code.append(m_name);
  code.append("&& ");
  code.append(m_rhs);
  code.append(")");

  return code;
}

QString Class::toDo(const QString& task, unsigned int indent)
{
  QString code = leadingWhitespace(1 + indent);
  code.append("// TODO ");
  code.append(task);
  code.append("\n");
  return code;
}

QString Class::toDoImplementation(unsigned int indent)
{
  return toDo("do implementation", indent);
}

void Class::setClassName(const QString& className)
{
  m_name = className;
}

void Class::setNamespaceNames(const QStringList& namespaceNames)
{
  m_namespaceNames = namespaceNames;
}

void Class::setInterfaces(const QList<Interface> &interfaces)
{
  m_interfaces = interfaces;
}

void Class::setBaseClass(const Class* baseClass)
{
  m_baseClass = baseClass;
}

void Class::setIndent(const QString& indent)
{
  m_indent = indent;
}

void Class::setDeclareConstructorExplicit(bool declareConstructorExplicit)
{
  m_declareConstructorExplicit = declareConstructorExplicit;
}

void Class::setDeclareDestructorVirtual(bool declareDestructorVirtual)
{
  m_declareDestructorVirtual = declareDestructorVirtual;
}

void Class::setIncludeQObjectMacro(bool includeQObjectMacro)
{
  m_includeQObjectMacro = includeQObjectMacro;
}

void Class::setConstructorDeclarationType(Class::DeclarationType constructorDeclarationType)
{
  m_constructorDeclarationType = constructorDeclarationType;
}

void Class::setDPointerType(Class::DPointerType dPointerType)
{
  m_dPointerType = dPointerType;
}

void Class::setDestructorDeclarationType(Class::DeclarationType destructorDeclarationType)
{
  m_destructorDeclarationType = destructorDeclarationType;
}

void Class::setCopyConstructorDeclarationType(Class::DeclarationType copyConstructorDeclarationType)
{
  m_copyConstructorDeclarationType = copyConstructorDeclarationType;
}

void Class::setCopyOperatorDeclarationType(Class::DeclarationType copyOperatorDeclarationType)
{
  m_copyOperatorDeclarationType = copyOperatorDeclarationType;
}

void Class::setMoveConstructorDeclarationType(Class::DeclarationType moveConstructorDeclarationType)
{
  m_moveConstructorDeclarationType = moveConstructorDeclarationType;
}

void Class::setMoveOperatorDeclarationType(Class::DeclarationType moveOperatorDeclarationType)
{
  m_moveOperatorDeclarationType = moveOperatorDeclarationType;
}

void Class::setSingletonType(Class::SingletonType singletonType)
{
  m_singletonType = singletonType;
}

void Class::checkOptions()
{
  if (m_dPointerType != DPointerType::NoDPointer)
  {
    if (m_copyConstructorDeclarationType == DeclarationType::NoDeclaration)
    {
      m_copyConstructorDeclarationType = DeclarationType::Public;
    }

    if (m_copyOperatorDeclarationType == DeclarationType::NoDeclaration)
    {
      m_copyOperatorDeclarationType = DeclarationType::Public;
    }

    // TODO support move constructor/operator
    m_moveConstructorDeclarationType = DeclarationType::NoDeclaration;
    m_moveOperatorDeclarationType = DeclarationType::NoDeclaration;
  }

  if (m_singletonType != SingletonType::NoSingleton)
  {
    m_constructorDeclarationType = DeclarationType::Private;
    m_destructorDeclarationType = DeclarationType::Private;
    m_copyConstructorDeclarationType = DeclarationType::Private;
    m_copyOperatorDeclarationType = DeclarationType::Private;

    if (m_moveConstructorDeclarationType != DeclarationType::NoDeclaration)
    {
      m_moveConstructorDeclarationType = DeclarationType::Private;
    }

    if (m_moveOperatorDeclarationType != DeclarationType::NoDeclaration)
    {
      m_moveOperatorDeclarationType = DeclarationType::Private;
    }
  }
}

void Class::append(QString& code, unsigned int indent, const QString& toAppend)
{
  code.append(leadingWhitespace(indent));
  code.append(toAppend);
}

void Class::appendLine(QString& code, unsigned int indent, const QString& toAppend)
{
  append(code, indent, toAppend);
  code.append("\n");
}

void Class::setOutputDirectory(const QString& outputDirectory)
{
  m_outputDirectory = outputDirectory;
}

void Class::setOverwriteExistingFiles(bool overwriteExistingFiles)
{
  m_overwriteExistingFiles = overwriteExistingFiles;
}

void Class::setUppercaseHeaderGuard(bool uppercaseHeaderGuard)
{
  m_uppercaseHeaderGuard = uppercaseHeaderGuard;
}

void Class::setMethods(const QList<Method>& methods)
{
  m_methods = methods;
}

QString Class::leadingWhitespace(unsigned int indent)
{
  QString leadingWhitespace;

  unsigned int totalIndent = indent + m_namespaceNames.size();

  for (unsigned int i = 0; i < totalIndent; i++)
  {
    leadingWhitespace.append(m_indent);
  }

  return leadingWhitespace;
}

QString Class::namespaceStart()
{
  QString code;

  unsigned int qtyIndent = 0;

  for (auto it = m_namespaceNames.begin(); it != m_namespaceNames.end(); it++)
  {
    for (unsigned int i = 0; i < qtyIndent; i++)
    {
      code.append(m_indent);
    }

    code.append("namespace ");
    code.append(*it);
    code.append("\n");

    for (unsigned int i = 0; i < qtyIndent; i++)
    {
      code.append(m_indent);
    }

    code.append("{\n");

    qtyIndent++;
  }

  return code;
}

QString Class::namespaceEnd()
{
  QString code;

  for (int i = m_namespaceNames.length(); i > 0; i--)
  {
    for (int j = 0; j < (i - 1); j++)
    {
      code.append(m_indent);
    }

    code.append("}\n");
  }

  return code;
}

QString Class::headerGuardStart()
{
  QString code;

  code.append("#ifndef ");
  code.append(headerGuard());
  code.append("\n");

  code.append("#define ");
  code.append(headerGuard());
  code.append("\n\n");

  return code;
}

QString Class::headerGuardEnd()
{
  QString code;

  code.append("\n#endif // ");
  code.append(headerGuard());

  return code;
}

QString Class::headerGuard()
{
  QString code;

  for (auto it = m_namespaceNames.begin(); it != m_namespaceNames.end(); it++)
  {
    code.append(m_uppercaseHeaderGuard ? it->toUpper() : *it);
    code.append("_");
  }

  code.append(m_uppercaseHeaderGuard ? m_name.toUpper() : m_name);
  code.append(m_uppercaseHeaderGuard ? "_H" : "_h");

  return code;
}

QString Class::includes()
{
  QString code;

  bool includeLineAdded = false;

  if (m_baseClass != 0)
  {
    code.append(include(m_baseClass->name(), true, false));
    includeLineAdded = true;

  }

  for (auto it = m_interfaces.begin(); it != m_interfaces.end(); it++)
  {
    if (!it->name().isEmpty())
    {
      code.append(include(it->name(), true, false));
      includeLineAdded = true;
    }

  }

  if (includeLineAdded)
  {
    code.append("\n");
  }

  return code;
}

QString Class::section(const QString& sectionName)
{
  m_sectionEmtpy = true;

  QString code = leadingWhitespace(0);
  code.append(sectionName);
  code.append(":\n");
  return code;
}
