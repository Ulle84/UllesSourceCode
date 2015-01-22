#include <QStringList>
#include <QFile>
#include <QDir>

#include "CodeGenerator.h"

CodeGenerator::CodeGenerator()
{
}

CodeGenerator::~CodeGenerator()
{
}

void CodeGenerator::generateCode(const Options& options)
{
  m_options = options;

  switch (m_options.m_type)
  {
  case Options::Class:
    generateCodeHeader();
    generateCodeClass();
    if (m_options.m_usePimpl)
    {
      generateCodePimpl();
    }
    break;
  case Options::Singleton:
    generateCodeHeader();
    generateCodeClass();
  //default:
  }

}

bool CodeGenerator::saveCode(const QString &fileName, const QStringList &code)
{
  // TODO check if file exist and ask user what to to

  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    return false;
  }

  qint64 bytesWritten = file.write(code.join("\n").toStdString().c_str());

  file.close();

  return bytesWritten < 1 ? false : true;
}

void CodeGenerator::generateCodeHeader()
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

  QString fileName = m_options.m_folder + QDir::separator() + m_options.m_className + ".h";
  saveCode(fileName, code);
}

void CodeGenerator::generateCodeClass()
{
  QStringList code;

  // includes
  code.append(QString("#include \"%1.h\"").arg(m_options.m_className));

  if (m_options.m_usePimpl)
  {
    code.append(QString("#include \"%1Impl.h\"").arg(m_options.m_className));
    code.append(QString(""));
    code.append(QString("#include <utility>"));
  }

  code.append(QString(""));

  // constructor
  code.append(QString("%1::%1()").arg(m_options.m_className));

  if (m_options.m_usePimpl)
  {
    code.append(QString("  : m_pImpl(new %1Impl())").arg(m_options.m_className));
  }

  code.append(QString("{"));
  code.append(QString("}"));
  code.append(QString(""));

  if (m_options.m_usePimpl)
  {
    // copy constructor
    code.append(QString("%1::%1(const %1& rhs)").arg(m_options.m_className));
    code.append(QString("  : m_pImpl(new %1Impl(*rhs.m_pImpl))").arg(m_options.m_className));
    code.append(QString("{"));
    code.append(QString("}"));
    code.append(QString(""));

    // move constructor
    code.append(QString("%1::%1(%1&& rhs)").arg(m_options.m_className));
    code.append(QString("  : m_pImpl(nullptr)"));
    code.append(QString("{"));
    code.append(QString("  std::swap(m_pImpl, rhs.m_pImpl);"));
    code.append(QString("}"));
    code.append(QString(""));

    // assignment operator
    code.append(QString("%1& %1::operator=(const %1& rhs)").arg(m_options.m_className));
    code.append(QString("{"));
    code.append(QString("  if(this != &rhs)"));
    code.append(QString("  {"));
    code.append(QString("    *m_pImpl = *(rhs.m_pImpl);"));
    code.append(QString("  }"));
    code.append(QString("  return *this;"));
    code.append(QString("}"));
    code.append(QString(""));
  }

  // destructor
  code.append(QString("%1::~%1()").arg(m_options.m_className));
  code.append(QString("{"));

  if (m_options.m_usePimpl)
  {
    code.append(QString("  delete m_pImpl;"));
  }

  code.append(QString("}"));

  QString fileName = m_options.m_folder + QDir::separator() + m_options.m_className + ".cpp";
  saveCode(fileName, code);
}

void CodeGenerator::generateCodePimpl()
{
  QStringList code;
  code.append(QString("#ifndef %1IMPL_H").arg(m_options.m_className.toUpper()));
  code.append(QString("#define %1IMPL_H").arg(m_options.m_className.toUpper()));
  code.append(QString(""));
  code.append(QString("#include \"%1.h\"").arg(m_options.m_className));
  code.append(QString(""));
  code.append(QString("class %1::%1Impl").arg(m_options.m_className));
  code.append(QString("{"));
  code.append(QString("public:"));
  code.append(QString(""));
  code.append(QString("};"));
  code.append(QString(""));

  //code.append(QString(""));
  //code.append(QString("%1").arg(m_className));

  code.append(QString("#endif // %1IMPL_H").arg(m_options.m_className.toUpper()));

  QString fileName = m_options.m_folder + QDir::separator() + m_options.m_className + "Impl.h";
  saveCode(fileName, code);
}
