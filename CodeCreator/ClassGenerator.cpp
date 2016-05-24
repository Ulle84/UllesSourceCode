#include <QFile>
#include <QTextStream>

#include "ClassGenerator.h"

ClassGenerator::ClassGenerator()
  : m_indent("  "),
    m_declareConstructorExplicit(false),
    m_declareDestructorVirtual(false),
    m_includeQObjectMacro(false),
    m_constructorDeclarationType(DeclarationType::PUBLIC),
    m_destructorDeclarationType(DeclarationType::PUBLIC),
    m_copyConstructorDeclarationType(DeclarationType::NONE),
    m_copyOperatorDeclarationType(DeclarationType::NONE),
    m_moveConstructorDeclarationType(DeclarationType::NONE),
    m_moveOperatorDeclarationType(DeclarationType::NONE),
    m_overwriteExistingFiles(false),
    m_uppercaseHeaderGuard(false)
{
}

QString ClassGenerator::createHeader()
{
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

  if (m_constructorDeclarationType == DeclarationType::PUBLIC)
  {
    code.append(constructorDeclaration());
  }

  if (m_copyConstructorDeclarationType == DeclarationType::PUBLIC)
  {
    code.append(copyConstructorDeclaration());
  }

  if (m_moveConstructorDeclarationType == DeclarationType::PUBLIC)
  {
    code.append(moveConstructorDeclaration());
  }

  if (m_copyOperatorDeclarationType == DeclarationType::PUBLIC)
  {
    code.append(copyOperatorDeclaration());
  }

  if (m_moveOperatorDeclarationType == DeclarationType::PUBLIC)
  {
    code.append(moveOperatorDeclaration());
  }

  if (m_destructorDeclarationType == DeclarationType::PUBLIC)
  {
    code.append(destructorDeclaration());
  }


  if (m_constructorDeclarationType == DeclarationType::PRIVATE
      || m_copyConstructorDeclarationType == DeclarationType::PRIVATE
      || m_copyOperatorDeclarationType == DeclarationType::PRIVATE
      || m_moveConstructorDeclarationType == DeclarationType::PRIVATE
      || m_moveOperatorDeclarationType == DeclarationType::PRIVATE
      || m_destructorDeclarationType == DeclarationType::PRIVATE)
  {
    code.append("\n");
    code.append(section("private"));
  }

  if (m_constructorDeclarationType == DeclarationType::PRIVATE)
  {
    code.append(constructorDeclaration());
  }

  if (m_copyConstructorDeclarationType == DeclarationType::PRIVATE)
  {
    code.append(copyConstructorDeclaration());
  }

  if (m_moveConstructorDeclarationType == DeclarationType::PRIVATE)
  {
    code.append(moveConstructorDeclaration());
  }

  if (m_copyOperatorDeclarationType == DeclarationType::PRIVATE)
  {
    code.append(copyOperatorDeclaration());
  }

  if (m_moveOperatorDeclarationType == DeclarationType::PRIVATE)
  {
    code.append(moveOperatorDeclaration());
  }

  if (m_destructorDeclarationType == DeclarationType::PRIVATE)
  {
    code.append(destructorDeclaration());
  }

  code.append(leadingWhitespace(false));
  code.append("};\n");
  code.append(namespaceEnd());
  code.append(headerGuardEnd());

  return code;
}

QString ClassGenerator::createImplementation()
{
  QString code;

  code.append(include(m_className));
  code.append("\n");

  code.append(namespaceStart());

  bool alreadyOneImplementationPresent = false;
  if (m_constructorDeclarationType == DeclarationType::PUBLIC)
  {
    code.append(constructorImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_copyConstructorDeclarationType == DeclarationType::PUBLIC)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }
    code.append(copyConstructorImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_moveConstructorDeclarationType == DeclarationType::PUBLIC)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }
    code.append(moveConstructorImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_copyOperatorDeclarationType == DeclarationType::PUBLIC)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }
    code.append(copyOperatorImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_moveOperatorDeclarationType == DeclarationType::PUBLIC)
  {
    if (alreadyOneImplementationPresent)
    {
      code.append("\n");
    }
    code.append(moveOperatorImplementation());
    alreadyOneImplementationPresent = true;
  }

  if (m_destructorDeclarationType == DeclarationType::PUBLIC)
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
  if (!createFile(FileType::HEADER))
  {
    return false;
  }

  if (!createFile(FileType::SOURCE))
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
  if (m_copyConstructorDeclarationType == DeclarationType::NONE)
  {
    return QString();
  }

  QString code = leadingWhitespace(true);

  code.append(m_className);
  code.append(constRef());

  if (m_copyConstructorDeclarationType == DeclarationType::PRIVATE)
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
  if (m_moveConstructorDeclarationType == DeclarationType::NONE)
  {
    return QString();
  }

  QString code = leadingWhitespace(true);

  code.append(m_className);
  code.append(moveRef());

  if (m_copyConstructorDeclarationType == DeclarationType::PRIVATE)
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
  if (m_copyOperatorDeclarationType == DeclarationType::NONE)
  {
    return QString();
  }

  QString code = leadingWhitespace(true);

  code.append(m_className);
  code.append("& operator= ");
  code.append(constRef());

  if (m_copyOperatorDeclarationType == DeclarationType::PRIVATE)
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
  if (m_moveOperatorDeclarationType == DeclarationType::NONE)
  {
    return QString();
  }

  QString code = leadingWhitespace(true);

  code.append(m_className);
  code.append("& operator= ");
  code.append(moveRef());

  if (m_copyOperatorDeclarationType == DeclarationType::PRIVATE)
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

  if (m_declareDestructorVirtual || m_destructorDeclarationType == DeclarationType::PRIVATE)
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

  if (fileType == FileType::HEADER)
  {
    textStream << createHeader();
  }
  else if (fileType == FileType::SOURCE)
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
  case FileType::HEADER:
    suffix = ".h";
    break;

  case FileType::SOURCE:
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

  code.append(leadingWhitespace(false));
  code.append("{\n\n");
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
