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
  mOptions = options;

  switch (mOptions.type)
  {
  case Options::Class:
    generateCodeHeader();
    generateCodeClass();
    if (mOptions.usePimpl)
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
  QDir dir(options.folderInput);

  dir.setNameFilters(options.files);

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
      QString line = in.readLine();
      for (auto it = options.searchAndReplace.begin(); it != options.searchAndReplace.end(); ++it)
      {
        line.replace(it.key(), it.value());
        line.replace(it.key().toUpper(), it.value().toUpper());
      }
      fileContent.append(line);
    }

    QString outputFileName = *it;

    for (auto it = options.searchAndReplace.begin(); it != options.searchAndReplace.end(); ++it)
    {
      outputFileName.replace(it.key(), it.value());
    }

    QFile output(options.folderOutput + QDir::separator() + outputFileName);

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
  code.append(QString("#ifndef %1_H").arg(mOptions.name.toUpper()));
  code.append(QString("#define %1_H").arg(mOptions.name.toUpper()));
  code.append(QString(""));

  if (mOptions.useInheritance)
  {
    code.append(QString("#include \"%1.h\"").arg(mOptions.baseClassName));
    code.append(QString(""));
    code.append(QString("class %1 : %2 %3").arg(mOptions.name).arg(mOptions.inheritanceType).arg(mOptions.baseClassName));
  }
  else
  {
    code.append(QString("class %1").arg(mOptions.name));
  }

  code.append(QString("{"));
  code.append(QString("public:"));

  code.append(QString("  %1();").arg(mOptions.name));
  code.append(QString("  ~%1();").arg(mOptions.name));

  if (mOptions.usePimpl && !mOptions.disableCopy)
  {
    code.append(QString());
    code.append(QString("  %1(const %1& rhs);").arg(mOptions.name));
    code.append(QString("  %1(%1&& rhs);").arg(mOptions.name));
    code.append(QString("  %1& operator=(const %1& rhs);").arg(mOptions.name));
  }

  if (mOptions.disableCopy || mOptions.usePimpl)
  {
    code.append(QString(""));
    code.append(QString("private:"));
  }

  if (mOptions.disableCopy)
  {
    code.append(QString("  %1(const %1& rhs);").arg(mOptions.name));
    code.append(QString("  %1(%1&& rhs);").arg(mOptions.name));
    code.append(QString("  %1& operator=(const %1& rhs);").arg(mOptions.name));
  }

  if (mOptions.disableCopy && mOptions.usePimpl)
  {
    code.append(QString(""));
  }

  if (mOptions.usePimpl)
  {
    code.append(QString("  class %1Impl;").arg(mOptions.name));
    code.append(QString("  %2Impl* m_pImpl;").arg(mOptions.name));
  }

  code.append(QString("};"));
  code.append(QString(""));

  //code.append(QString(""));
  //code.append(QString("%1").arg(m_className));

  code.append(QString("#endif // %1_H").arg(mOptions.name.toUpper()));

  QString fileName = mOptions.folder + QDir::separator() + mOptions.name + ".h";
  saveCode(fileName, code);
}

void CodeGenerator::generateCodeClass()
{
  QStringList code;

  // includes
  code.append(QString("#include \"%1.h\"").arg(mOptions.name));

  if (mOptions.usePimpl)
  {
    code.append(QString("#include \"%1Impl.h\"").arg(mOptions.name));
    code.append(QString(""));
    code.append(QString("#include <utilities>"));
  }

  code.append(QString(""));

  // constructor
  code.append(QString("%1::%1()").arg(mOptions.name));

  if (mOptions.usePimpl)
  {
    code.append(QString("  : m_pImpl(new %1Impl())").arg(mOptions.name));
  }

  code.append(QString("{"));
  code.append(QString("}"));
  code.append(QString(""));

  if (mOptions.usePimpl && !mOptions.disableCopy)
  {
    // copy constructor
    code.append(QString("%1::%1(const %1& rhs)").arg(mOptions.name));
    code.append(QString("  : m_pImpl(new %1Impl(*rhs.m_pImpl))").arg(mOptions.name));
    code.append(QString("{"));
    code.append(QString("}"));
    code.append(QString(""));

    // move constructor
    code.append(QString("%1::%1(%1&& rhs)").arg(mOptions.name));
    code.append(QString("  : m_pImpl(nullptr)"));
    code.append(QString("{"));
    code.append(QString("  std::swap(m_pImpl, rhs.m_pImpl);"));
    code.append(QString("}"));
    code.append(QString(""));

    // assignment operator
    code.append(QString("%1& %1::operator=(const %1& rhs)").arg(mOptions.name));
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
  code.append(QString("%1::~%1()").arg(mOptions.name));
  code.append(QString("{"));
  if (mOptions.usePimpl)
  {
    code.append(QString("  delete m_pImpl;"));
  }
  code.append(QString("}"));
  code.append(QString(""));

  QString fileName = mOptions.folder + QDir::separator() + mOptions.name + ".cpp";
  saveCode(fileName, code);
}

void CodeGenerator::generateCodePimpl()
{
  QStringList code;
  code.append(QString("#ifndef %1IMPL_H").arg(mOptions.name.toUpper()));
  code.append(QString("#define %1IMPL_H").arg(mOptions.name.toUpper()));
  code.append(QString(""));
  code.append(QString("#include \"%1.h\"").arg(mOptions.name));
  code.append(QString(""));
  code.append(QString("class %1::%1Impl").arg(mOptions.name));
  code.append(QString("{"));
  code.append(QString("public:"));
  code.append(QString(""));
  code.append(QString("};"));
  code.append(QString(""));

  //code.append(QString(""));
  //code.append(QString("%1").arg(m_className));

  code.append(QString("#endif // %1IMPL_H").arg(mOptions.name.toUpper()));

  QString fileName = mOptions.folder + QDir::separator() + mOptions.name + "Impl.h";
  saveCode(fileName, code);
}
