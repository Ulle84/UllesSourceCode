#include "ProjectCleanerConfirmation.h"
#include "ui_ProjectCleanerConfirmation.h"

ProjectCleanerConfirmation::ProjectCleanerConfirmation(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ProjectCleanerConfirmation)
{
  ui->setupUi(this);
}

ProjectCleanerConfirmation::~ProjectCleanerConfirmation()
{
  delete ui;
}

void ProjectCleanerConfirmation::setFilesToDelete(const QStringList &filesToDelete)
{
  ui->plainTextEditFilesToDelete->setPlainText(filesToDelete.join("\n"));
}
