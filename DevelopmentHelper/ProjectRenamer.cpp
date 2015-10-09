#include "ProjectRenamer.h"
#include "ui_ProjectRenamer.h"

ProjectRenamer::ProjectRenamer(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ProjectRenamer)
{
  ui->setupUi(this);
}

ProjectRenamer::~ProjectRenamer()
{
  delete ui;
}
