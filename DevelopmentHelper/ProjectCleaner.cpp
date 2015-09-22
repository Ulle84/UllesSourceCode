#include <QDebug>
#include <QDirIterator>
#include <QFile>
#include <QFileDialog>
#include <QSettings>

#include "ProjectCleaner.h"
#include "ProjectCleanerConfirmation.h"
#include "ui_ProjectCleaner.h"

ProjectCleaner::ProjectCleaner(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ProjectCleaner)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "DevelopmentHelper.ProjectCleaner", this);

  if (m_settings->contains("directory"))
  {
    m_directory = m_settings->value("directory").toString();
  }
  if (m_settings->contains("filter"))
  {
    ui->lineEditFilter->setText(m_settings->value("filter").toString());
  }
}

ProjectCleaner::~ProjectCleaner()
{
  m_settings->setValue("directory", m_directory);
  m_settings->setValue("filter", ui->lineEditFilter->text());

  delete ui;
}

void ProjectCleaner::on_pushButtonChooseDirectory_clicked()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"), m_directory, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.isEmpty())
  {
    return;
  }

  m_directory = directory;

  QStringList filePatterns = ui->lineEditFilter->text().split(";");
  QStringList filesToDelete;

  QDirIterator it(m_directory, filePatterns, QDir::Files | QDir::AllEntries | QDir::Hidden | QDir::System, QDirIterator::Subdirectories);
  while (it.hasNext())
  {
    filesToDelete.append(it.next());
  }

  ProjectCleanerConfirmation projectCleanerConfirmation;
  projectCleanerConfirmation.setFilesToDelete(filesToDelete);

  if (projectCleanerConfirmation.exec() == QDialog::Accepted)
  {
    for (auto it = filesToDelete.begin(); it != filesToDelete.end(); it++)
    {
      QFile file(*it);
      file.remove();
    }
  }
}
