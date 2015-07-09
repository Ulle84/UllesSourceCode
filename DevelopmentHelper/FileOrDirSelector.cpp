#include "FileOrDirSelector.h"
#include "ui_FileOrDirSelector.h"

#include <QFileDialog>
#include <QClipboard>

FileOrDirSelector::FileOrDirSelector(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::FileOrDirSelector)
{
  ui->setupUi(this);
}

FileOrDirSelector::~FileOrDirSelector()
{
  delete ui;
}

void FileOrDirSelector::on_pushButtonSelectBaseFolder_clicked()
{
  QString directory = QFileDialog::getExistingDirectory();

  if (directory.isEmpty())
  {
    return;
  }

  baseFolder = directory;
  updateLineEditFields();
}

void FileOrDirSelector::updateLineEditFields()
{
  QDir baseDir(baseFolder);
  ui->lineEditBaseFolder->setText(baseFolder);

  QString lineEditRelativeFileText = baseDir.relativeFilePath(relativeFile).replace("/", "\\");

  if (ui->checkBoxProject->isChecked())
  {
    lineEditRelativeFileText = "$(ProjectDir)" + lineEditRelativeFileText;
  }

  if (ui->checkBoxSolution->isChecked())
  {
    lineEditRelativeFileText = "$(SolutionDir)" + lineEditRelativeFileText;
  }

  ui->lineEditRelativeFile->setText(lineEditRelativeFileText);

  QString lineEditRelativeFolderText = baseDir.relativeFilePath(relativeFolder).replace("/", "\\");

  if (baseFolder == relativeFolder || baseFolder + "\\" == relativeFolder)
  {
    lineEditRelativeFolderText = ".";
  }

  if (ui->checkBoxProject->isChecked())
  {
    lineEditRelativeFolderText = "$(ProjectDir)" + lineEditRelativeFolderText;
  }

  if (ui->checkBoxSolution->isChecked())
  {
    lineEditRelativeFolderText = "$(SolutionDir)" + lineEditRelativeFolderText;
  }

  ui->lineEditRelativeFolder->setText(lineEditRelativeFolderText);
}

void FileOrDirSelector::on_pushButtonSelectRelativeFolder_clicked()
{
  QString directory = QFileDialog::getExistingDirectory();

  if (directory.isEmpty())
  {
    return;
  }

  relativeFolder = directory;
  updateLineEditFields();
}

void FileOrDirSelector::on_pushButtonSelectRelativeFile_clicked()
{
  QString file = QFileDialog::getOpenFileName();

  if (file.isEmpty())
  {
    return;
  }

  relativeFile = file;
  updateLineEditFields();
}

void FileOrDirSelector::on_pushButtonCopyBaseFolderToClipboard_clicked()
{
  QApplication::clipboard()->setText(ui->lineEditBaseFolder->text());
}

void FileOrDirSelector::on_pushButtonCopyRelativeFolderToClipboard_clicked()
{
  QApplication::clipboard()->setText(ui->lineEditRelativeFolder->text());
}

void FileOrDirSelector::on_pushButtonCopyRelativeFileToClipboard_clicked()
{
  QApplication::clipboard()->setText(ui->lineEditRelativeFile->text());
}



void FileOrDirSelector::on_lineEditBaseFolder_textEdited(const QString& arg1)
{
  if (QFile(ui->lineEditBaseFolder->text()).exists())
  {
    baseFolder = ui->lineEditBaseFolder->text();
    updateLineEditFields();
  }
  else
  {
    ui->lineEditRelativeFile->clear();
    ui->lineEditRelativeFolder->clear();
  }
}

void FileOrDirSelector::on_checkBoxProject_clicked(bool checked)
{
  if (checked)
  {
    ui->checkBoxSolution->setChecked(false);
  }

  updateLineEditFields();
}

void FileOrDirSelector::on_checkBoxSolution_clicked(bool checked)
{
  if (checked)
  {
    ui->checkBoxProject->setChecked(false);
  }

  updateLineEditFields();
}
