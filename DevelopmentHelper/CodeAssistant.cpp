#include <QClipboard>

#include "ForLoopCreator.h"
#include "IterateOverContainer.h"
#include "FindInContainer.h"
#include "ConnectionHelper.h"
#include "EnumHelper.h"

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
  ConnectionHelper* connectionHelper = new ConnectionHelper(this);
  EnumHelper* enumHelper = new EnumHelper(this);

  ui->container->layout()->addWidget(forLoopCreator);
  ui->container->layout()->addWidget(iterateOverContainer);
  ui->container->layout()->addWidget(findInContainer);
  ui->container->layout()->addWidget(connectionHelper);
  ui->container->layout()->addWidget(enumHelper);
}

CodeAssistant::~CodeAssistant()
{
  delete ui;
}
