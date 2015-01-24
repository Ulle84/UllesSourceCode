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

bool CodeGenerator::copyFromTemplate(const Options& options)
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
