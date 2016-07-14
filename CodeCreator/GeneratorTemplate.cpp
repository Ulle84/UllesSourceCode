#include <QFile>
#include <QTextStream>

#include "ui_GeneratorTemplate.h"

#include "GeneratorTemplate.h"
#include "XmlHelper.h"

GeneratorTemplate::GeneratorTemplate(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorTemplate)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorTemplate::~GeneratorTemplate()
{
  delete ui;
}

void GeneratorTemplate::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorTemplate::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
}

QList<QPair<QString, QString> > GeneratorTemplate::generatedCode()
{
  QList<QPair<QString, QString> > code;

  QString name = ui->lineEditName->text();

  QStringList files;
  files.append(":/files/GeneratorTemplate/GeneratorTemplate.h");
  files.append(":/files/GeneratorTemplate/GeneratorTemplate.cpp");
  files.append(":/files/GeneratorTemplate/GeneratorTemplate.ui");

  for (auto it = files.begin(); it != files.end(); it++)
  {
    QFile file(*it);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
      return code;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    fileContent.replace("Template", name);

    QStringList splitted = it->split("/");
    QString fileName = splitted.last();
    fileName.replace("Template", name);

    code.append(qMakePair(fileName, fileContent));
  }

  return code;
}
