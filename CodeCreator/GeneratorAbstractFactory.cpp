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
  factoryInterface.setName(abstractFactoryName);
  for (auto it = products.begin(); it != products.end(); it++)
  {
    Method method;
    method.setName("create" + it->name());
    method.setReturnType(CodeHelper::interfaceName(it->name()) + '*');
    factoryInterface.append(method);
  }

  // abstract factory
  Class abstractFactory(abstractFactoryName);
  abstractFactory.setInterface(factoryInterface, true);

  QStringList productInterfaceNames;
  for (auto it = products.begin(); it != products.end(); ++it)
  {
    productInterfaceNames.append(CodeHelper::classNameToHeader(CodeHelper::interfaceName(it->name())));
  }
  abstractFactory.setDeclarationIncludes(productInterfaceNames);

  QList<QPair<QString, QString> > code;
  code.append(qMakePair(abstractFactoryName + ".h", abstractFactory.declaration()));

  // concrete factories
  for (auto it = concreteFactories.begin(); it != concreteFactories.end(); it++)
  {
    QStringList includes;
    Interface concreteFactoryInterface;
    concreteFactoryInterface.setName(abstractFactoryName);
    for (auto it2 = products.begin(); it2 != products.end(); it2++)
    {
      Method method;
      method.setName("create" + it2->name());
      method.setReturnType(CodeHelper::interfaceName(it2->name()) + '*');
      method.setImplementationBody("return new " + *it + it2->name() + "();");
      concreteFactoryInterface.append(method);
      includes.append("\"" + *it + it2->name() + ".h\"");
    }

    Class concreteFactory(*it);
    concreteFactory.setInterfaces(QList<Interface>() << concreteFactoryInterface);
    concreteFactory.setImplementationIncludes(includes);

    code.append(qMakePair(*it + ".h", concreteFactory.declaration()));
    code.append(qMakePair(*it + ".cpp", concreteFactory.implementation()));
  }

  // abstract product interfaces
  for (auto it = products.begin(); it != products.end(); ++it)
  {
    QString productInterfaceName = CodeHelper::interfaceName(it->name());
    Class product(productInterfaceName);
    product.setInterface(*it, true);

    code.append(qMakePair(productInterfaceName + ".h", product.declaration()));
  }

  // concrete product classes
  for (auto it = concreteFactories.begin(); it != concreteFactories.end(); it++)
  {
    for (auto it2 = products.begin(); it2 != products.end(); it2++)
    {
      QString productName = *it + it2->name();
      Interface productInterface = *it2;
      productInterface.setName(CodeHelper::interfaceName(it2->name()));

      Class product(productName);
      product.setInterfaces(QList<Interface>() << productInterface);

      code.append(qMakePair(productName + ".h", product.declaration()));
      code.append(qMakePair(productName + ".cpp", product.implementation()));
    }
  }

  return code;
}
