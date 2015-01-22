#include "Generator.h"
#include "ui_Generator.h"

#include <QDir>
#include <QFile>
#include <QStringList>
#include <QTextStream>

Generator::Generator(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Generator),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Generator::~Generator()
{
  delete ui;
}

void Generator::generate(const QString &folder)
{
  // take all files from source
  QDir dir("templates/CodeCreator/");

  QStringList filters;
  filters << "CodeCreator.h" << "CodeCreator.cpp" << "CodeCreator.ui";
  dir.setNameFilters(filters);

  QStringList fileNames = dir.entryList();

  // open them and read to QStringList
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
      fileContent.append(in.readLine().replace("CodeCreator", ui->lineEditName->text()).replace("CODECREATOR", ui->lineEditName->text().toUpper()));
    }

    QFile output(folder + QDir::separator() + (*it).replace("CodeCreator", ui->lineEditName->text()));

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

void Generator::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      ui->lineEditName->setText(xml.readElementText());
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Generator::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
}
