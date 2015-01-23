#include "Interface.h"
#include "ui_Interface.h"

#include "Options.h"
#include "CodeGenerator.h"

Interface::Interface(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Interface),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Interface::~Interface()
{
  delete ui;
}

void Interface::generate(const QString &folder)
{
  QStringList functions = ui->plainTextEditFunctions->toPlainText().split("\n");

  for (auto it = functions.begin(); it != functions.end(); ++it)
  {
    QString simplified = it->simplified();

    if (simplified.isEmpty())
    {
      continue;
    }
    else
    {
      if (simplified.left(2) == "//")
      {
        *it = simplified.prepend("  ");
      }
      else
      {
        *it = simplified.remove(";").prepend("  virtual ").append(" = 0;");
      }
    }
  }

  Options options;
  options.folderOutput = folder;
  options.folderInput = "templates/Interface/";
  options.searchAndReplace["Interface"] = ui->lineEditName->text();
  options.searchAndReplace["  // TODO add functions here"] = functions.join("\n");

  options.files << "Interface.h";

  m_codeGenerator->copyFromTemplate(options);
}

void Interface::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      ui->lineEditName->setText(xml.readElementText());
    }
    else if (xml.name() == "Prefix")
    {
      ui->checkBoxPrefix->setChecked(xml.readElementText() == "true");
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Interface::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
  xml.writeTextElement("Prefix", ui->checkBoxPrefix->isChecked() ? "true" : "false");
}
