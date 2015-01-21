#include <QStringList>

#include "CodeGenerator.h"
#include "CodeSaver.h"

CodeGenerator::CodeGenerator()
  : m_codeSaver(new CodeSaver())
{
}

CodeGenerator::~CodeGenerator()
{
  delete m_codeSaver;
}

void CodeGenerator::generateCode(const Options& options)
{
  m_options = options;
  //TODO analyse options and generate code

  switch (m_options.m_type)
  {
  case Options::Class:
    generateCodeHeader();
    break;
  //default:
  }

}

QStringList CodeGenerator::generateCodeHeader()
{
  QStringList code;
  code.append(QString("#ifndef %1_H").arg(m_options.m_className.toUpper()));
  code.append(QString("#define %1_H").arg(m_options.m_className.toUpper()));
  code.append(QString(""));

  if (m_options.m_useInheritance)
  {
    code.append(QString("#include \"%1.h\"").arg(m_options.m_baseClassName));
    code.append(QString(""));
    code.append(QString("class %1 : %2 %3").arg(m_options.m_className).arg(m_options.m_inheritanceType).arg(m_options.m_baseClassName));
  }
  else
  {
    code.append(QString("class %1").arg(m_options.m_className));
  }

  code.append(QString("{"));
  code.append(QString("public:"));
  code.append(QString("  %1();").arg(m_options.m_className));

  if (m_options.m_usePimpl && !m_options.m_disableCopy)
  {
    code.append(QString("  %1(const %1& rhs);").arg(m_options.m_className));
    code.append(QString("  %1(%1&& rhs);").arg(m_options.m_className));
    code.append(QString("  %1& operator=(const %1& rhs);").arg(m_options.m_className));
  }

  code.append(QString("  ~%1();").arg(m_options.m_className));

  if (m_options.m_disableCopy || m_options.m_usePimpl)
  {
    code.append(QString(""));
    code.append(QString("private:"));
  }

  if (m_options.m_disableCopy)
  {
    code.append(QString("  %1(const %1& rhs);").arg(m_options.m_className));
    code.append(QString("  %1(%1&& rhs);").arg(m_options.m_className));
    code.append(QString("  %1& operator=(const %1& rhs);").arg(m_options.m_className));
  }

  if (m_options.m_disableCopy && m_options.m_usePimpl)
  {
    code.append(QString(""));
  }

  if (m_options.m_usePimpl)
  {
    code.append(QString("  class %1Impl;").arg(m_options.m_className));
    code.append(QString("  %1Impl* m_pImpl;").arg(m_options.m_className));
  }

  code.append(QString("};"));
  code.append(QString(""));

  //code.append(QString(""));
  //code.append(QString("%1").arg(m_className));

  code.append(QString("#endif // %1_H").arg(m_options.m_className.toUpper()));

  return code;
}
