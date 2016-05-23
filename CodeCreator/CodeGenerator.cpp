#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>

#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(QWidget *parent) :
  QWidget(parent)
{
}

CodeGenerator::~CodeGenerator()
{
}

void CodeGenerator::setBasePath(const QString &basePath)
{
  m_basePath = basePath;
}

bool CodeGenerator::copyFromTemplate(const Options& options)
{
  QString directory = m_basePath + QDir::separator() + options.folderInput;
  QDir dir(directory);

  if (!dir.exists())
  {
    QMessageBox mb;
    mb.setText(tr("Cannot open template directory %1").arg(directory));
    mb.exec();
    return false;
  }

  dir.setNameFilters(options.files);

  QStringList fileNames = dir.entryList();

  for (auto it = options.files.begin(); it != options.files.end(); it++)
  {
    if (!fileNames.contains(*it))
    {
      QMessageBox mb;
      mb.setText(tr("Cannot find template file %1!").arg(*it));
      mb.exec();
      return false;
    }
  }

  for (auto it = fileNames.begin(); it != fileNames.end(); ++it)
  {
    QString filePath = dir.filePath(*it);

    QFile input(filePath);

    if (!input.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QMessageBox mb;
      mb.setText(tr("Cannot open template file %1!").arg(filePath));
      mb.exec();
      return false;
    }

    QStringList fileContent;
    QTextStream in(&input);
    while (!in.atEnd())
    {
      QString line = in.readLine();

      // TODO remove after implementing searchAndReplaceList
      /*for (auto it = options.searchAndReplace.begin(); it != options.searchAndReplace.end(); ++it)
      {
        line.replace(it.key(), it.value());
        line.replace(it.key().toUpper(), it.value().toUpper());
      }*/

      for (auto it = options.searchAndReplace.begin(); it != options.searchAndReplace.end(); ++it)
      {
        line.replace(it->first, it->second);
        line.replace(it->first.toUpper(), it->second.toUpper());
      }

      fileContent.append(line);
    }

    QString outputFileName = *it;

    // TODO remove after implementing searchAndReplaceList
    /*for (auto it = options.searchAndReplace.begin(); it != options.searchAndReplace.end(); ++it)
    {
      outputFileName.replace(it.key(), it.value());
    }*/

    for (auto it = options.searchAndReplace.begin(); it != options.searchAndReplace.end(); ++it)
    {
      outputFileName.replace(it->first, it->second);
    }

    QFile output(options.folderOutput + QDir::separator() + outputFileName);

    if (output.exists())
    {
      if (QMessageBox::No == QMessageBox::warning(this, tr("File already exist!"), tr("Do you want to overwrite the existing file %1?").arg(outputFileName), QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
      {
        return false;
      }
    }

    if (!output.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      QMessageBox mb;
      mb.setText(tr("Cannot open output file %1!").arg(outputFileName));
      mb.exec();
      return false;
    }    

    QTextStream out(&output);
    out << fileContent.join("\n");
  }
  return true;
}


