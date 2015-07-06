#include "DevelopmentHelper.h"
#include "ui_DevelopmentHelper.h"

#include "StashHelper.h"

DevelopmentHelper::DevelopmentHelper(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DevelopmentHelper)
{
  ui->setupUi(this);

  stashHelper = new StashHelper();

  ui->tabWidget->addTab(stashHelper, "Stash");
}

DevelopmentHelper::~DevelopmentHelper()
{
  delete ui;
}
