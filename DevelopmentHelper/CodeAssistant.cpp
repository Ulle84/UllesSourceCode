#include <QClipboard>

#include "ForLoopCreator.h"
#include "IterateOverContainer.h"
#include "FindInContainer.h"

#include "CodeAssistant.h"
#include "ui_CodeAssistant.h"

CodeAssistant::CodeAssistant(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::CodeAssistant)
{
  ui->setupUi(this);

  ForLoopCreator* forLoopCreator = new ForLoopCreator(this);
  IterateOverContainer* iterateOverContainer = new IterateOverContainer(this);
  FindInContainer* findInContainer = new FindInContainer(this);

  ui->container->layout()->addWidget(forLoopCreator);
  ui->container->layout()->addWidget(iterateOverContainer);
  ui->container->layout()->addWidget(findInContainer);
}

CodeAssistant::~CodeAssistant()
{
  delete ui;
}
