#include "DevelopmentHelper.h"
#include "ui_DevelopmentHelper.h"

DevelopmentHelper::DevelopmentHelper(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DevelopmentHelper)
{
  ui->setupUi(this);
}

DevelopmentHelper::~DevelopmentHelper()
{
  delete ui;
}
