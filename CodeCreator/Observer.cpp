#include "Observer.h"
#include "ui_Observer.h"

Observer::Observer(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Observer),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Observer::~Observer()
{
  delete ui;
}

void Observer::generate(const QString &folder)
{
}

void Observer::readXml(QXmlStreamReader &xml)
{
}

void Observer::writeXml(QXmlStreamWriter &xml)
{
}
