#include <QStringList>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>

#include "CodeGenerator.h"

CodeGenerator::CodeGenerator()
{
}

CodeGenerator::~CodeGenerator()
{
}

bool CodeGenerator::copyFromTemplate(const Options& options)
{
  // TODO show errors and return false in case

  QDir dir(options.folderInput);

  dir.setNameFilters(options.files);

  QStringList fileNames = dir.entryList();

  for (auto it = fileNames.begin(); it != fileNames.end(); ++it)
  {
    QString filePath = dir.filePath(*it);

    QFile input(filePath);

    if (input.exists())
    {
      // TODO
      /*int reply = QMessageBox::warning(this, tr("File already exist!"), tr("Do you want to overwrite the existing file %1?").arg(*it));
      if (reply == QMessageBox::No)
      {
        return false;
      }*/
    }

    if (!input.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QMessageBox mb;
      // TODO tr mb.setText(tr("Cannot open file %1!").arg(*it));
      mb.setText(QString("Cannot open file %1!").arg(*it));
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

    if (!output.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      continue;
    }

    QTextStream out(&output);
    out << fileContent.join("\n");

    output.close();
    input.close();
  }
  return true;
}
