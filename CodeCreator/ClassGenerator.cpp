#include <QFile>
#include <QTextStream>

#include "ClassGenerator.h"

ClassGenerator::ClassGenerator()
  : m_indent("  "),
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
    m_singletonType(SingletonType::NoSingleton)
{
}

QString ClassGenerator::createHeader()
{
  checkOptions();

  QString code;

  code.append(headerGuardStart());
  code.append(baseClassIncludes());
  code.append(namespaceStart());
  code.append(classDeclaration());

  if (m_includeQObjectMacro)
  {
    code.append(leadingWhitespace(true));
    code.append("Q_OBJECT\n\n");
  }

  code.append(section("public"));

  if (m_singletonType != SingletonType::NoSingleton)
  {
    code.append(singletonGetInstanceDeclaration());
  }

  if (m_constructorDeclarationType == DeclarationType::Public)
  {
    code.append(constructorDeclaration());
  }

  if (m_copyConstructorDeclarationType == DeclarationType::Public)
  {
    code.append(copyConstructorDeclaration());
  }

  if (m_moveConstructorDeclarationType == DeclarationType::Public)
  {
    code.append(moveConstructorDeclaration());
  }

  if (m_copyOperatorDeclarationType == DeclarationType::Public)
  {
    code.append(copyOperatorDeclaration());
  }

  if (m_moveOperatorDeclarationType == DeclarationType::Public)
  {
    code.append(moveOperatorDeclaration());
  }

  if (m_destructorDeclarationType == DeclarationType::Public)
  {
    code.append(destructorDeclaration());
  }

  if (m_constructorDeclarationType == DeclarationType::Private
      || m_copyConstructorDeclarationType == DeclarationType::Private
      || m_copyOperatorDeclarationType == DeclarationType::Private
      || m_moveConstructorDeclarationType == DeclarationType::Private
      || m_moveOperatorDeclarationType == DeclarationType::Private
      || m_destructorDeclarationType == DeclarationType::Private
      || m_singletonType != SingletonType::NoSingleton)
  {
    code.append("\n");
    code.append(section("private"));
  }

  if (m_constructorDeclarationType == DeclarationType::Private)
  {
    code.append(constructorDeclaration());
  }

  if (m_copyConstructorDeclarationType == DeclarationType::Private)
  {
    code.append(copyConstructorDeclaration());
  }

  if (m_moveConstructorDeclarationType == DeclarationType::Private)
  {
    code.append(moveConstructorDeclaration());
  }

  if (m_copyOperatorDeclarationType == DeclarationType::Private)
  {
    code.append(copyOperatorDeclaration());
  }

  if (m_moveOperatorDeclarationType == DeclarationType::Private)
  {
    code.append(moveOperatorDeclaration());
  }

  if (m_destructorDeclarationType == DeclarationType::Private)
  {
    code.append(destructorDeclaration());
  }

  if (m_singletonType != SingletonType::NoSingleton)
  {
    code.append("\n");
    code.append(singletonInstance());
  }

  code.append(leadingWhitespace(false));
  code.append("};\n");
  code.append(namespaceEnd());
  code.append(headerGuardEnd());

  return code;
}

QString ClassGenerator::createImplementation()
{
  checkOptions();

  QString code;

  code.append(include(m_className));
  code.append("\n");

  code.append(namespaceStart());

  bool alreadyOneImplementationPresent = false;

  if (m_singletonType == SingletonType::Eager)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }

    code.append(singletonInitialization());
    alreadyOneImplementationPresent = true;
  }

  if (m_singletonType != SingletonType::NoSingleton)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }

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

  if (m_destructorDeclarationType == DeclarationType::Public)
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

bool ClassGenerator::createFiles()
{
  if (!createFile(FileType::Header))
  {
    return false;
  }

  if (!createFile(FileType::Source))
  {
    return false;
  }

  return true;
}

QString ClassGenerator::constructorDeclaration()
{
  QString code = leadingWhitespace(true);

  if (m_declareConstructorExplicit)
  {
    code.append("explicit ");
  }

  code.append(m_className);
  code.append("();\n");

  return code;
}

QString ClassGenerator::constructorImplementation()
{
  QString code = leadingWhitespace(false);

  code.append(m_className);
  code.append("::");
  code.append(m_className);
  code.append("()\n");
  code.append(emptyBlock());

  return code;
}

QString ClassGenerator::copyConstructorDeclaration()
{
  if (m_copyConstructorDeclarationType == DeclarationType::NoDeclaration)
  {
    return QString();
  }

  QString code = leadingWhitespace(true);

  code.append(m_className);
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

QString ClassGenerator::copyConstructorImplementation()
{
  QString code = leadingWhitespace(false);

  code.append(m_className);
  code.append("::");
  code.append(m_className);
  code.append(constRef());
  code.append("\n");
  code.append(emptyBlock());

  return code;
}

QString ClassGenerator::moveConstructorDeclaration()
{
  if (m_moveConstructorDeclarationType == DeclarationType::NoDeclaration)
  {
    return QString();
  }

  QString code = leadingWhitespace(true);

  code.append(m_className);
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

QString ClassGenerator::moveConstructorImplementation()
{
  QString code = leadingWhitespace(false);

  code.append(m_className);
  code.append("::");
  code.append(m_className);
  code.append(moveRef());
  code.append("\n");
  code.append(emptyBlock());

  return code;
}

QString ClassGenerator::copyOperatorDeclaration()
{
  if (m_copyOperatorDeclarationType == DeclarationType::NoDeclaration)
  {
    return QString();
  }

  QString code = leadingWhitespace(true);

  code.append(m_className);
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

QString ClassGenerator::copyOperatorImplementation()
{
  QString code = leadingWhitespace(false);

  code.append(m_className);
  code.append("& ");
  code.append(m_className);
  code.append("::operator=");
  code.append(constRef());
  code.append("\n{\n");
  code.append(toDoImplementation());
  code.append(leadingWhitespace(true));
  code.append("return *this;\n");
  code.append(leadingWhitespace(false));
  code.append("}\n");

  return code;
}

QString ClassGenerator::moveOperatorDeclaration()
{
  if (m_moveOperatorDeclarationType == DeclarationType::NoDeclaration)
  {
    return QString();
  }

  QString code = leadingWhitespace(true);

  code.append(m_className);
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

QString ClassGenerator::moveOperatorImplementation()
{
  QString code = leadingWhitespace(false);

  code.append(m_className);
  code.append("& ");
  code.append(m_className);
  code.append("::operator=");
  code.append(moveRef());
  code.append("\n{\n");
  code.append(toDoImplementation());
  code.append(leadingWhitespace(true));
  code.append("return *this;\n");
  code.append(leadingWhitespace(false));
  code.append("}\n");

  return code;
}

QString ClassGenerator::destructorDeclaration()
{
  QString code = leadingWhitespace(true);

  if (m_declareDestructorVirtual)
  {
    code.append("virtual ");
  }

  code.append("~");
  code.append(m_className);
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

QString ClassGenerator::destructorImplementation()
{
  QString code = leadingWhitespace(false);

  code.append(m_className);
  code.append("::~");
  code.append(m_className);
  code.append("()\n");
  code.append(emptyBlock());

  return code;
}

QString ClassGenerator::singletonInstance()
{
  QString code = leadingWhitespace(true);

  code.append("static ");
  code.append(m_className);
  code.append("* m_instance;\n");

  return code;
}

QString ClassGenerator::singletonInitialization()
{
  QString code = leadingWhitespace(false);

  code.append(m_className);
  code.append("* ");
  code.append(m_className);
  code.append("::m_instance = new ");
  code.append(m_className);
  code.append("();\n");

  return code;
}

QString ClassGenerator::singletonGetInstanceDeclaration()
{
  QString code = leadingWhitespace(true);

  code.append("static ");
  code.append(m_className);
  code.append("* getInstance();\n");

  return code;
}

QString ClassGenerator::singletonGetInstanceImplementation()
{
  QString code = leadingWhitespace(false);

  code.append(m_className);
  code.append("* ");
  code.append(m_className);
  code.append("::getInstance()\n");
  code.append(openBlock());
  code.append(leadingWhitespace(true));
  code.append("return m_instance;\n");
  code.append(closeBlock());

  return code;
}

bool ClassGenerator::createFile(FileType fileType)
{
  QString suffix = getSuffix(fileType);

  QString fileName = m_outputDirectory + m_className + suffix;

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

QString ClassGenerator::getSuffix(ClassGenerator::FileType fileType)
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

QString ClassGenerator::classDeclaration()
{
  QString code = leadingWhitespace(false);

  code.append("class ");
  code.append(m_className);

  if (!m_baseClasses.isEmpty())
  {
    code.append(" : ");

    for (auto it = m_baseClasses.begin(); it != m_baseClasses.end(); it++)
    {
      if (it != m_baseClasses.begin())
      {
        code.append(", ");
      }

      code.append("public ");
      code.append(*it);
    }
  }

  code.append("\n");
  code.append(leadingWhitespace(false));
  code.append("{\n");

  return code;
}

QString ClassGenerator::include(const QString& header)
{
  QString code;

  code.append("#include \"");
  code.append(header);
  code.append(".h\"\n");

  return code;
}

QString ClassGenerator::emptyBlock()
{
  QString code;

  code.append(openBlock());
  code.append("\n");
  code.append(closeBlock());

  return code;
}

QString ClassGenerator::openBlock()
{
  QString code;

  code.append(leadingWhitespace(false));
  code.append("{\n");

  return code;
}

QString ClassGenerator::closeBlock()
{
  QString code;

  code.append(leadingWhitespace(false));
  code.append("}\n");

  return code;
}

QString ClassGenerator::constRef()
{
  QString code;

  code.append("(const ");
  code.append(m_className);
  code.append("& rhs)");

  return code;
}

QString ClassGenerator::moveRef()
{
  QString code;

  code.append("(");
  code.append(m_className);
  code.append("&& rhs)");

  return code;
}

QString ClassGenerator::toDo(const QString& task)
{
  QString code = leadingWhitespace(true);
  code.append("// TODO ");
  code.append(task);
  code.append("\n");
  return code;
}

QString ClassGenerator::toDoImplementation()
{
  return toDo("do implementation");
}

void ClassGenerator::setClassName(const QString& className)
{
  m_className = className;
}

void ClassGenerator::setNamespaceNames(const QStringList& namespaceNames)
{
  m_namespaceNames = namespaceNames;
}

void ClassGenerator::setBaseClasses(const QStringList& baseClasses)
{
  m_baseClasses = baseClasses;
}

void ClassGenerator::setIndent(const QString& indent)
{
  m_indent = indent;
}

void ClassGenerator::setDeclareConstructorExplicit(bool declareConstructorExplicit)
{
  m_declareConstructorExplicit = declareConstructorExplicit;
}

void ClassGenerator::setDeclareDestructorVirtual(bool declareDestructorVirtual)
{
  m_declareDestructorVirtual = declareDestructorVirtual;
}

void ClassGenerator::setIncludeQObjectMacro(bool includeQObjectMacro)
{
  m_includeQObjectMacro = includeQObjectMacro;
}

void ClassGenerator::setConstructorDeclarationType(ClassGenerator::DeclarationType constructorDeclarationType)
{
  m_constructorDeclarationType = constructorDeclarationType;
}

void ClassGenerator::setDestructorDeclarationType(ClassGenerator::DeclarationType destructorDeclarationType)
{
  m_destructorDeclarationType = destructorDeclarationType;
}

void ClassGenerator::setCopyConstructorDeclarationType(ClassGenerator::DeclarationType copyConstructorDeclarationType)
{
  m_copyConstructorDeclarationType = copyConstructorDeclarationType;
}

void ClassGenerator::setCopyOperatorDeclarationType(ClassGenerator::DeclarationType copyOperatorDeclarationType)
{
  m_copyOperatorDeclarationType = copyOperatorDeclarationType;
}

void ClassGenerator::setMoveConstructorDeclarationType(ClassGenerator::DeclarationType moveConstructorDeclarationType)
{
  m_moveConstructorDeclarationType = moveConstructorDeclarationType;
}

void ClassGenerator::setMoveOperatorDeclarationType(ClassGenerator::DeclarationType moveOperatorDeclarationType)
{
  m_moveOperatorDeclarationType = moveOperatorDeclarationType;
}

void ClassGenerator::setSingletonType(ClassGenerator::SingletonType singletonType)
{
  m_singletonType = singletonType;
}

void ClassGenerator::checkOptions()
{
  if (m_singletonType != SingletonType::NoSingleton)
  {
    m_constructorDeclarationType = DeclarationType::Private;
    m_destructorDeclarationType = DeclarationType::NoDeclaration;
    m_copyConstructorDeclarationType = DeclarationType::Private;
    m_copyOperatorDeclarationType = DeclarationType::Private;
    m_moveConstructorDeclarationType = DeclarationType::Private;
    m_moveOperatorDeclarationType = DeclarationType::Private;
  }
}

void ClassGenerator::setOutputDirectory(const QString& outputDirectory)
{
  m_outputDirectory = outputDirectory;
}

void ClassGenerator::setOverwriteExistingFiles(bool overwriteExistingFiles)
{
  m_overwriteExistingFiles = overwriteExistingFiles;
}

void ClassGenerator::setUppercaseHeaderGuard(bool uppercaseHeaderGuard)
{
  m_uppercaseHeaderGuard = uppercaseHeaderGuard;
}

QString ClassGenerator::leadingWhitespace(bool indent)
{
  QString leadingWhitespace;

  if (indent)
  {
    leadingWhitespace.append(m_indent);
  }

  for (int i = 0; i < m_namespaceNames.size(); i++)
  {
    leadingWhitespace.append(m_indent);
  }

  return leadingWhitespace;
}

QString ClassGenerator::namespaceStart()
{
  QString code;

  unsigned int qtyIndent = 0;

  for (auto it = m_namespaceNames.begin(); it != m_namespaceNames.end(); it++)
  {
    for (unsigned int i = 0; i < qtyIndent; i++)
    {
      code.append(m_indent);
    }

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

QString ClassGenerator::namespaceEnd()
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

QString ClassGenerator::headerGuardStart()
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

QString ClassGenerator::headerGuardEnd()
{
  QString code;

  code.append("\n#endif // ");
  code.append(headerGuard());

  return code;
}

QString ClassGenerator::headerGuard()
{
  QString code;

  for (auto it = m_namespaceNames.begin(); it != m_namespaceNames.end(); it++)
  {
    code.append(m_uppercaseHeaderGuard ? it->toUpper() : *it);
    code.append("_");
  }

  code.append(m_uppercaseHeaderGuard ? m_className.toUpper() : m_className);

  code.append(m_uppercaseHeaderGuard ? "_H" : "_h");

  return code;
}

QString ClassGenerator::baseClassIncludes()
{
  QString code;

  for (auto it = m_baseClasses.begin(); it != m_baseClasses.end(); it++)
  {
    code.append(include(*it));
  }

  if (!m_baseClasses.isEmpty())
  {
    code.append("\n");
  }

  return code;
}

QString ClassGenerator::section(const QString& sectionName)
{
  QString code = leadingWhitespace(false);
  code.append(sectionName);
  code.append(":\n");
  return code;
}
