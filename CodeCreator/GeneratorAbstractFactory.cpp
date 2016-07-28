#include <QDebug>

#include "ui_GeneratorAbstractFactory.h"

#include "Class.h"
#include "CodeHelper.h"
#include "GeneratorAbstractFactory.h"
#include "XmlHelper.h"

GeneratorAbstractFactory::GeneratorAbstractFactory(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorAbstractFactory)
{
  ui->setupUi(this);

  ui->productEditor->setToImplementAvailable(false);
  ui->productEditor->setDialogTitle(tr("procuct editor"));
  ui->productEditor->setButtonText(tr("add product"));

  connect(ui->lineEditAbstractFactory, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->plainTextEditConcreteFactories, SIGNAL(textChanged()), this, SIGNAL(optionsChanged()));
  connect(ui->productEditor, SIGNAL(interfaceListChanged()), this, SIGNAL(optionsChanged()));
}

GeneratorAbstractFactory::~GeneratorAbstractFactory()
{
  delete ui;
}

void GeneratorAbstractFactory::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "AbstractFactory")
    {
      XmlHelper::readXml(xml, ui->lineEditAbstractFactory);
    }
    else if (xml.name() == "ConcreteFactories")
    {
      XmlHelper::readXml(xml, ui->plainTextEditConcreteFactories);
    }
    else if (xml.name() == "Products")
    {
      QList<Interface> interfaces;
      XmlHelper::readXml(xml, &interfaces);
      ui->productEditor->setInterfaceList(interfaces);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorAbstractFactory::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "AbstractFactory", ui->lineEditAbstractFactory);
  XmlHelper::writeXml(xml, "ConcreteFactories", ui->plainTextEditConcreteFactories);
  QList<Interface> interfaceList = ui->productEditor->interfaceList();
  XmlHelper::writeXml(xml, "Products", &interfaceList);
}

QList<QPair<QString, QString> > GeneratorAbstractFactory::generatedCode()
{
  QString abstractFactoryName = CodeHelper::interfaceName(ui->lineEditAbstractFactory->text());
  QStringList concreteFactories = ui->plainTextEditConcreteFactories->toPlainText().split('\n', QString::SkipEmptyParts);

  QList<Interface> products = ui->productEditor->interfaceList();

  Interface factoryInterface;
  for (auto it = products.begin(); it != products.end(); it++)
  {
    Method method;
    method.setName("create" + it->name());
    method.setReturnType(CodeHelper::interfaceName(it->name()) + '*');
    factoryInterface.append(method);
    //productNames.append(it->name());
  }

  // TODO read product list
  // TODO create abstract factory interface
  // TODO create concrete factories
  // TODO create abstract product interfaces
  // TODO create concrete product classes

  Class abstractFactory(abstractFactoryName);
  abstractFactory.setInterface(factoryInterface, true);

  QList<QPair<QString, QString> > code;
  code.append(qMakePair(abstractFactoryName + ".h", abstractFactory.declaration()));

  /*for (auto it = concreteFactories.begin(); it != concreteFactories.end(); it++)
  {
    code.append(qMakePair(*it + ".h", QString("TODO Declaration")));
    code.append(qMakePair(*it + ".cpp", QString("TODO Implementation")));
  }*/

  return code;
}
