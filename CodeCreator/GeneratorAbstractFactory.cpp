#include "ui_GeneratorAbstractFactory.h"

#include "GeneratorAbstractFactory.h"
#include "XmlHelper.h"

GeneratorAbstractFactory::GeneratorAbstractFactory(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorAbstractFactory)
{
  ui->setupUi(this);

  connect(ui->lineEditFactory, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
}

GeneratorAbstractFactory::~GeneratorAbstractFactory()
{
  delete ui;
}

void GeneratorAbstractFactory::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Factory")
    {
      XmlHelper::readXml(xml, ui->lineEditFactory);
    }
    // TODO add further members here
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorAbstractFactory::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Factory", ui->lineEditFactory);
  // TODO add further members here
}

QList<QPair<QString, QString> > GeneratorAbstractFactory::generatedCode()
{
  QString name = ui->lineEditFactory->text();

  QList<QPair<QString, QString> > code;
  code.append(qMakePair(name + ".h", QString("TODO Declaration")));
  code.append(qMakePair(name + ".cpp", QString("TODO Implementation")));
  return code;
}
