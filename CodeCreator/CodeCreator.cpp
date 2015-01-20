#include "CodeCreator.h"
#include "ui_CodeCreator.h"

#include "ClassGenerator.h"
#include "InterfaceGenerator.h"
#include "SingletonGenerator.h"

CodeCreator::CodeCreator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator),
  m_currentGenerator(nullptr)
{
  ui->setupUi(this);
  initGenerators();
}

CodeCreator::~CodeCreator()
{
  delete ui;
}

void CodeCreator::initGenerators()
{
  m_generators["Class"] = new ClassGenerator(this);
  m_generators["Interface"] = new InterfaceGenerator(this);
  m_generators["Singleton"] = new SingletonGenerator(this);

  for (auto it = m_generators.begin(); it != m_generators.end(); ++it)
  {
    if (it == m_generators.begin())
    {
      m_currentGenerator = it->second;
    }
    else
    {
      it->second->setVisible(false);
    }

    ui->comboBoxType->addItem(it->first);
    ui->generators->layout()->addWidget(it->second);
  }
}

void CodeCreator::on_comboBoxType_currentIndexChanged(const QString &type)
{
  m_currentGenerator->setVisible(false);
  m_currentGenerator = m_generators[type];
  m_currentGenerator->setVisible(true);

}
