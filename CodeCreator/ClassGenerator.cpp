#include "ClassGenerator.h"

ClassGenerator::ClassGenerator()
  : m_indent("  ")
{
}

QString ClassGenerator::createClass(const Options &options)
{
  QString code;

  code.append(headerGuardStart());
  code.append(baseClassIncludes());
  code.append(namespaceStart());
  code.append(classDeclaration(options));
  code.append(section("public"));
  code.append(constructorDeclaration(options));
  code.append(destructorDeclaration(options));
  code.append(leadingWhitespace(false));
  code.append("}\n");
  code.append(namespaceEnd());
  code.append(headerGuardEnd());

  return code;
}

QString ClassGenerator::constructorDeclaration(const Options &options)
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

QString ClassGenerator::destructorDeclaration(const Options &options)
{
  QString code = leadingWhitespace(true);

  if (options.declareDestructorVirtual)
  {
    code.append("virtual ");
  }

  code.append("~");
  code.append(m_className);
  code.append("();\n");

  return code;
}

QString ClassGenerator::classDeclaration(const ClassGenerator::Options &options)
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



void ClassGenerator::setClassName(const QString &className)
{
  m_className = className;
}

void ClassGenerator::setNamespaceNames(const QStringList &namespaceNames)
{
  m_namespaceNames = namespaceNames;
}

void ClassGenerator::setBaseClasses(const QStringList &baseClasses)
{
  m_baseClasses = baseClasses;
}

void ClassGenerator::setIndent(const QString &indent)
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
    for (int j = 0; j < (i-1); j++)
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
  QString code = m_className.toUpper();

  code.append("_H");

  return code;
}

QString ClassGenerator::baseClassIncludes()
{
  QString code;

  for (auto it = m_baseClasses.begin(); it != m_baseClasses.end(); it++)
  {
    code.append("#include ");
    code.append(*it);
    code.append(".h\n");
  }

  if (!m_baseClasses.isEmpty())
  {
    code.append("\n");
  }

  return code;
}

QString ClassGenerator::section(const QString &sectionName)
{
  QString code = leadingWhitespace(false);
  code.append(sectionName);
  code.append(":\n");
  return code;
}
