#include <QStringList>
#include <QFile>
#include <QDir>
#include <QTextStream>
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
    break;
  case Options::Interface:
    generateCodeHeader();
    break;
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

void CodeGenerator::copyFromTemplate(const OptionsTemplate &options)
{
  QDir dir(options.m_folderInput);

  dir.setNameFilters(options.m_files);

  QStringList fileNames = dir.entryList();

  for (auto it = fileNames.begin(); it != fileNames.end(); ++it)
  {
    QString filePath = dir.filePath(*it);

    QFile input(filePath);

    if (!input.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      continue;
    }

    QStringList fileContent;
    QTextStream in(&input);
    while (!in.atEnd())
    {
      fileContent.append(in.readLine().replace(options.m_searchString, options.m_replaceString).replace(QString(options.m_searchString).toUpper(), options.m_replaceString.toUpper()));
    }

    QFile output(options.m_folderOutput + QDir::separator() + (*it).replace(options.m_searchString, options.m_replaceString));

    if (!output.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      continue;
    }

    QTextStream out(&output);
    out << fileContent.join("\n");

    output.close();
    input.close();
  }
}

void CodeGenerator::generateCodeHeader()
{
  QStringList code;
  code.append(QString("#ifndef %1_H").arg(m_options.m_name.toUpper()));
  code.append(QString("#define %1_H").arg(m_options.m_name.toUpper()));
  code.append(QString(""));

  if (m_options.m_singleton)
  {
    code.append(QString("#include <QMutex>"));
    code.append(QString(""));
  }

  if (m_options.m_useInheritance)
  {
    code.append(QString("#include \"%1.h\"").arg(m_options.m_baseClassName));
    code.append(QString(""));
    code.append(QString("class %1 : %2 %3").arg(m_options.m_name).arg(m_options.m_inheritanceType).arg(m_options.m_baseClassName));
  }
  else
  {
    code.append(QString("class %1").arg(m_options.m_name));
  }

  code.append(QString("{"));
  code.append(QString("public:"));

  if (!(m_options.m_interface || m_options.m_singleton))
  {
    code.append(QString("  %1();").arg(m_options.m_name));
    code.append(QString("  ~%1();").arg(m_options.m_name));
  }

  if (m_options.m_singleton)
  {
    code.append(QString("  static %1* getInstance();").arg(m_options.m_name));
  }

  if (m_options.m_interface)
  {
    QStringList functions = m_options.m_functions.split("\n");

    for (auto it = functions.begin(); it != functions.end(); ++it)
    {
      QString simplified = it->simplified();

      if (simplified.isEmpty())
      {
        code.append(simplified);
      }
      else
      {
        if (simplified.left(2) == "//")
        {
          code.append(simplified.prepend("  "));
        }
        else
        {
          code.append(simplified.remove(";").prepend("  virtual ").append(" = 0;"));
        }
      }
    }
  }

  if (m_options.m_usePimpl && !m_options.m_disableCopy)
  {
    code.append(QString());
    code.append(QString("  %1(const %1& rhs);").arg(m_options.m_name));
    code.append(QString("  %1(%1&& rhs);").arg(m_options.m_name));
    code.append(QString("  %1& operator=(const %1& rhs);").arg(m_options.m_name));
  }

  if (m_options.m_disableCopy || m_options.m_usePimpl)
  {
    code.append(QString(""));
    code.append(QString("private:"));
  }

  if (m_options.m_singleton)
  {
    code.append(QString("  %1();").arg(m_options.m_name));
    code.append(QString("  ~%1();").arg(m_options.m_name));
  }

  if (m_options.m_disableCopy)
  {
    code.append(QString("  %1(const %1& rhs);").arg(m_options.m_name));
    code.append(QString("  %1(%1&& rhs);").arg(m_options.m_name));
    code.append(QString("  %1& operator=(const %1& rhs);").arg(m_options.m_name));
  }

  if (m_options.m_disableCopy && m_options.m_usePimpl)
  {
    code.append(QString(""));
  }

  if (m_options.m_singleton)
  {
    code.append(QString("  static QMutex m_mutex;"));
    code.append(QString("  static %1* m_instance;").arg(m_options.m_name));
  }

  if (m_options.m_singleton && m_options.m_usePimpl)
  {
    code.append(QString(""));
  }

  if (m_options.m_usePimpl)
  {
    code.append(QString("  class %1Impl;").arg(m_options.m_name));
    code.append(QString("  %1%2Impl* m_pImpl;").arg(m_options.m_singleton ? "static " : "").arg(m_options.m_name));
  }

  code.append(QString("};"));
  code.append(QString(""));

  //code.append(QString(""));
  //code.append(QString("%1").arg(m_className));

  code.append(QString("#endif // %1_H").arg(m_options.m_name.toUpper()));

  QString fileName = m_options.m_folder + QDir::separator() + m_options.m_name + ".h";
  saveCode(fileName, code);
}

void CodeGenerator::generateCodeClass()
{
  QStringList code;

  // includes
  code.append(QString("#include \"%1.h\"").arg(m_options.m_name));

  if (m_options.m_usePimpl)
  {
    code.append(QString("#include \"%1Impl.h\"").arg(m_options.m_name));

    if (!m_options.m_singleton)
    {
      code.append(QString(""));
      code.append(QString("#include <utilities>"));
    }
  }

  code.append(QString(""));

  if (m_options.m_singleton)
  {
    code.append(QString("%1* %1::m_instance = nullptr;").arg(m_options.m_name));
    code.append(QString(""));
  }

  // constructor
  code.append(QString("%1::%1()").arg(m_options.m_name));

  if (m_options.m_usePimpl)
  {
    code.append(QString("  : m_pImpl(new %1Impl())").arg(m_options.m_name));
  }

  code.append(QString("{"));
  code.append(QString("}"));
  code.append(QString(""));

  if ((m_options.m_usePimpl && !m_options.m_disableCopy) && !m_options.m_singleton)
  {
    // copy constructor
    code.append(QString("%1::%1(const %1& rhs)").arg(m_options.m_name));
    code.append(QString("  : m_pImpl(new %1Impl(*rhs.m_pImpl))").arg(m_options.m_name));
    code.append(QString("{"));
    code.append(QString("}"));
    code.append(QString(""));

    // move constructor
    code.append(QString("%1::%1(%1&& rhs)").arg(m_options.m_name));
    code.append(QString("  : m_pImpl(nullptr)"));
    code.append(QString("{"));
    code.append(QString("  std::swap(m_pImpl, rhs.m_pImpl);"));
    code.append(QString("}"));
    code.append(QString(""));

    // assignment operator
    code.append(QString("%1& %1::operator=(const %1& rhs)").arg(m_options.m_name));
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
  code.append(QString("%1::~%1()").arg(m_options.m_name));
  code.append(QString("{"));
  if (m_options.m_usePimpl)
  {
    code.append(QString("  delete m_pImpl;"));
  }
  code.append(QString("}"));
  code.append(QString(""));

  // access to singleton
  if (m_options.m_singleton)
  {
    code.append(QString("%1* %1::getInstance()").arg(m_options.m_name));
    code.append(QString("{"));
    code.append(QString("  m_mutex.lock();"));
    code.append(QString("  if(m_instance == nullptr)"));
    code.append(QString("  {"));
    code.append(QString("    m_instance = new %1();").arg(m_options.m_name));
    code.append(QString("  }"));
    code.append(QString("  m_mutex.unlock();"));
    code.append(QString("  return m_instance;"));
    code.append(QString("}"));
  }

  QString fileName = m_options.m_folder + QDir::separator() + m_options.m_name + ".cpp";
  saveCode(fileName, code);
}

void CodeGenerator::generateCodePimpl()
{
  QStringList code;
  code.append(QString("#ifndef %1IMPL_H").arg(m_options.m_name.toUpper()));
  code.append(QString("#define %1IMPL_H").arg(m_options.m_name.toUpper()));
  code.append(QString(""));
  code.append(QString("#include \"%1.h\"").arg(m_options.m_name));
  code.append(QString(""));
  code.append(QString("class %1::%1Impl").arg(m_options.m_name));
  code.append(QString("{"));
  code.append(QString("public:"));
  code.append(QString(""));
  code.append(QString("};"));
  code.append(QString(""));

  //code.append(QString(""));
  //code.append(QString("%1").arg(m_className));

  code.append(QString("#endif // %1IMPL_H").arg(m_options.m_name.toUpper()));

  QString fileName = m_options.m_folder + QDir::separator() + m_options.m_name + "Impl.h";
  saveCode(fileName, code);
}
