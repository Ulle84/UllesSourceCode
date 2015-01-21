#include <QStringList>

#include "CodeGenerator.h"
#include "HeaderOptions.h"

CodeGenerator::CodeGenerator()
{
}

QStringList CodeGenerator::generateCodeHeader(const HeaderOptions &options)
{
  QStringList code;
  code.append(QString("#ifndef %1_H").arg(options.m_className.toUpper()));
  code.append(QString("#define %1_H").arg(options.m_className.toUpper()));
  code.append(QString(""));

  if (options.m_useInheritance)
  {
    code.append(QString("#include \"%1.h\"").arg(options.m_baseClassName));
    code.append(QString(""));
    code.append(QString("class %1 : %2 %3").arg(options.m_className).arg(options.m_inheritanceType).arg(options.m_baseClassName));
  }
  else
  {
    code.append(QString("class %1").arg(options.m_className));
  }

  code.append(QString("{"));
  code.append(QString("public:"));
  code.append(QString("  %1();").arg(options.m_className));

  if (options.m_usePimpl && !options.m_disableCopy)
  {
    code.append(QString("  %1(const %1& rhs);").arg(options.m_className));
    code.append(QString("  %1(%1&& rhs);").arg(options.m_className));
    code.append(QString("  %1& operator=(const %1& rhs);").arg(options.m_className));
  }

  code.append(QString("  ~%1();").arg(options.m_className));

  if (options.m_disableCopy || options.m_usePimpl)
  {
    code.append(QString(""));
    code.append(QString("private:"));
  }

  if (options.m_disableCopy)
  {
    code.append(QString("  %1(const %1& rhs);").arg(options.m_className));
    code.append(QString("  %1(%1&& rhs);").arg(options.m_className));
    code.append(QString("  %1& operator=(const %1& rhs);").arg(options.m_className));
  }

  if (options.m_disableCopy && options.m_usePimpl)
  {
    code.append(QString(""));
  }

  if (options.m_usePimpl)
  {
    code.append(QString("  class %1Impl;").arg(options.m_className));
    code.append(QString("  %1Impl* m_pImpl;").arg(options.m_className));
  }

  code.append(QString("};"));
  code.append(QString(""));

  //code.append(QString(""));
  //code.append(QString("%1").arg(m_className));

  code.append(QString("#endif // %1_H").arg(options.m_className.toUpper()));

  return code;
}

QStringList CodeGenerator::generateCodeClass(const ClassOptions &options)
{

}
