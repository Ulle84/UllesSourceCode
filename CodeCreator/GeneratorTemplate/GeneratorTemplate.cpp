#include "ui_GeneratorTemplate.h"

#include "Class.h"
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
    // TODO add further members here
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorTemplate::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  // TODO add further members here
}

QList<QPair<QString, QString> > GeneratorTemplate::generatedCode()
{
  QString name = ui->lineEditName->text();

  Class c(name);

  QList<QPair<QString, QString> > code;
  code.append(qMakePair(name + ".h", c.declaration()));
  code.append(qMakePair(name + ".cpp", c.implementation()));
  return code;
}
