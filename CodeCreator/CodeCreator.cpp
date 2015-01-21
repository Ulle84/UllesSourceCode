/*
 * TODO
 * CodeGenerator
 * CodeSaver
 * Class
 *   use Q_OBJECT Macro
 *   namespace
 *   export dll
 *   members + options getter/setter
 * Interface
 * Singleton
 */

#include "CodeCreator.h"
#include "ui_CodeCreator.h"

#include "CodeGenerator.h"

#include "ClassGenerator.h"
#include "InterfaceGenerator.h"
#include "SingletonGenerator.h"

CodeCreator::CodeCreator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator)
{
  ui->setupUi(this);
  m_codeGenerator = new CodeGenerator();
  initGenerators();
}

CodeCreator::~CodeCreator()
{
  delete m_codeGenerator;
  delete ui;
}

void CodeCreator::initGenerators()
{
  m_generators["Class"] = new ClassGenerator(m_codeGenerator, this);
  m_generators["Interface"] = new InterfaceGenerator(m_codeGenerator, this);
  m_generators["Singleton"] = new SingletonGenerator(m_codeGenerator, this);

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
