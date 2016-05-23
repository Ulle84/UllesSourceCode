#include <QFile>
#include <QTextStream>

#include "ClassGenerator.h"

ClassGenerator::ClassGenerator()
  : m_indent("  ")
{
}

QString ClassGenerator::createHeader(const Options& options)
{
  QString code;

  code.append(headerGuardStart());
  code.append(baseClassIncludes());
  code.append(namespaceStart());
  code.append(classDeclaration(options));

  if (options.includeQObjectMacro)
  {
    code.append(leadingWhitespace(true));
    code.append("Q_OBJECT\n\n");
  }

  code.append(section("public"));

  if (!options.declareConstrucorPrivate)
    code.append(constructorDeclaration(options));

  if (options.copyConstructor == DeclarationType::PUBLIC)
  {
    code.append(copyConstructorDeclaration(options));
  }

  if (options.copyOperator == DeclarationType::PUBLIC)
  {
    code.append(copyOperatorDeclaration(options));
  }

  code.append(destructorDeclaration(options));

  if (options.copyConstructor == DeclarationType::PRIVATE
      || options.copyOperator == DeclarationType::PRIVATE
      || options.declareConstrucorPrivate)
  {
    code.append("\n");
    code.append(section("private"));
  }

  if (options.declareConstrucorPrivate)
    code.append(constructorDeclaration(options));

  if (options.copyConstructor == DeclarationType::PRIVATE)
  {
    code.append(copyConstructorDeclaration(options));
  }

  if (options.copyOperator == DeclarationType::PRIVATE)
  {
    code.append(copyOperatorDeclaration(options));
  }

  code.append(leadingWhitespace(false));
  code.append("};\n");
  code.append(namespaceEnd());
  code.append(headerGuardEnd());

  return code;
}

QString ClassGenerator::createImplementation(const ClassGenerator::Options& options)
{
  QString code;

  code.append(include(m_className));
  code.append("\n");

  code.append(namespaceStart());
  code.append(constructorImplementation(options));

  if (options.copyConstructor == DeclarationType::PUBLIC)
  {
    code.append("\n");
    code.append(copyConstructorImplementation(options));
  }

  if (options.copyOperator == DeclarationType::PUBLIC)
  {
    code.append("\n");
    code.append(copyOperatorImplementation(options));
  }

  code.append("\n");
  code.append(destructorImplementation(options));

  code.append(namespaceEnd());

  return code;
}

bool ClassGenerator::createFiles(const ClassGenerator::Options& options)
{
  if (!createFile(options, FileType::HEADER))
  {
    return false;
  }

  if (!createFile(options, FileType::SOURCE))
  {
    return false;
  }

  return true;
}

QString ClassGenerator::constructorDeclaration(const Options& options)
{
  QString code = leadingWhitespace(true);

  if (options.declareConstructorExplicit)
  {
    code.append("explicit ");
  }

  code.append(m_className);
  code.append("();\n");

  return code;
}

QString ClassGenerator::constructorImplementation(const ClassGenerator::Options& options)
{
  QString code = leadingWhitespace(false);

  code.append(m_className);
  code.append("::");
  code.append(m_className);
  code.append("()\n");
  code.append(emptyBlock());

  return code;
}

QString ClassGenerator::copyConstructorDeclaration(const ClassGenerator::Options& options)
{
  if (options.copyConstructor == DeclarationType::NONE)
  {
    return QString();
  }

  QString code = leadingWhitespace(true);

  code.append(m_className);
  code.append(constRef());

  if (options.copyConstructor == DeclarationType::PRIVATE)
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

QString ClassGenerator::copyConstructorImplementation(const ClassGenerator::Options& options)
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

QString ClassGenerator::copyOperatorDeclaration(const ClassGenerator::Options& options)
{
  if (options.copyOperator == DeclarationType::NONE)
  {
    return QString();
  }

  QString code = leadingWhitespace(true);

  code.append(m_className);
  code.append("& operator= ");
  code.append(constRef());

  if (options.copyOperator == DeclarationType::PRIVATE)
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

QString ClassGenerator::copyOperatorImplementation(const ClassGenerator::Options& options)
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

QString ClassGenerator::destructorDeclaration(const Options& options)
{
  QString code = leadingWhitespace(true);

  if (options.declareDestructorVirtual)
  {
    code.append("virtual ");
  }

  code.append("~");
  code.append(m_className);
  code.append("()");

  if (options.declareDestructorVirtual)
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

QString ClassGenerator::destructorImplementation(const ClassGenerator::Options& options)
{
  QString code = leadingWhitespace(false);

  code.append(m_className);
  code.append("::~");
  code.append(m_className);
  code.append("()\n");
  code.append(emptyBlock());

  return code;
}

bool ClassGenerator::createFile(const ClassGenerator::Options& options, FileType fileType)
{
  QString suffix = getSuffix(fileType);

  QString fileName = options.outputDirectory + m_className + suffix;

  QFile file(fileName);

  if (file.exists() && !options.overwriteExistingFiles)
    return false;

  if (!file.open(QIODevice::WriteOnly))
    return false;

  QTextStream textStream(&file);

  if (fileType == FileType::HEADER)
    textStream << createHeader(options);
  else if (fileType == FileType::SOURCE)
    textStream << createImplementation(options);

  file.close();

  return true;
}

QString ClassGenerator::getSuffix(ClassGenerator::FileType fileType)
{
  QString suffix;

  switch(fileType)
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

QString ClassGenerator::classDeclaration(const ClassGenerator::Options& options)
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
    code.append(it->toUpper());
    code.append("_");
  }

  code.append(m_className.toUpper());

  code.append("_H");

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

ClassGenerator::Options::Options()
  : declareConstructorExplicit(false),
    declareDestructorVirtual(false),
    includeQObjectMacro(false),
    copyConstructor(NONE),
    overwriteExistingFiles(false),
    declareConstrucorPrivate(false)
{
}
