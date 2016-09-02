#include <QFileDialog>
#include <QDir>
#include <QSettings>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QTextStream>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "InfoFile.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_infoFileName("info.md")
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "DirectorySwitcher", this);

  if (m_settings->contains("currentDirectory"))
  {
    ui->lineEditBaseDirectory->setText(m_settings->value("currentDirectory").toString());
  }

  if (m_settings->contains("baseName"))
  {
    ui->lineEditBaseName->setText(m_settings->value("baseName").toString());
  }

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  checkDirectory();

  setWindowTitle("Directory Switcher");
}

MainWindow::~MainWindow()
{
  m_settings->setValue("currentDirectory", ui->lineEditBaseDirectory->text());
  m_settings->setValue("baseName", ui->lineEditBaseName->text());
  m_settings->setValue("geometry", geometry());

  delete ui;
}

void MainWindow::setWorkingDirectory(const QString& workingDirectory)
{
  QDir workDir(workingDirectory);

  if (workDir.exists())
  {
    ui->lineEditBaseName->setText(workDir.dirName());
    workDir.cdUp();
    ui->lineEditBaseDirectory->setText(workDir.absolutePath());
  }

  checkDirectory();
}

void MainWindow::on_pushButtonSelectDirectory_clicked()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("select directoy"), ui->lineEditBaseDirectory->text());

  if (!directory.isEmpty())
  {
    ui->lineEditBaseDirectory->setText(directory);
    checkDirectory();
  }
}

void MainWindow::on_pushButtonCheckDirectory_clicked()
{
  checkDirectory();
}

void MainWindow::checkDirectory()
{
  QDir dir(ui->lineEditBaseDirectory->text());

  if (!dir.exists())
  {
    showUserMessage(tr("directory does not exist!"));
  }

  QStringList filter;
  filter << ui->lineEditBaseName->text() + "*";
  dir.setNameFilters(filter);

  QStringList dirs = dir.entryList(filter, QDir::Dirs);

  if (dirs.empty())
  {
    return;
  }

  ui->listWidgetProjects->blockSignals(true);
  ui->listWidgetProjects->clear();

  for (auto it = dirs.begin(); it != dirs.end(); ++it)
  {
    ui->listWidgetProjects->addItem(*it);
  }
  ui->listWidgetProjects->blockSignals(false);

  if (ui->listWidgetProjects->count() > 0)
  {
    ui->listWidgetProjects->setCurrentRow(0);
  }
}

void MainWindow::updateInfo()
{
  ui->plainTextEditInformation->clear();
  InfoFile infoFile(m_currentInfoFile);

  ui->lineEditId->setText(infoFile.id());
  ui->plainTextEditInformation->setPlainText(infoFile.content());
}

void MainWindow::showUserMessage(QString message)
{
  QMessageBox messagebox;
  messagebox.setText(message);
  messagebox.exec();
  return;
}

void MainWindow::on_listWidgetProjects_currentTextChanged(const QString &currentText)
{
  m_currentInfoFile = ui->lineEditBaseDirectory->text() + QDir::separator() + currentText + QDir::separator() + m_infoFileName;
  updateInfo();
}
void MainWindow::on_pushButtonSave_clicked()
{
  if (ui->listWidgetProjects->currentRow() < 0)
  {
    showUserMessage(tr("select item in list first!"));
  }

  InfoFile infoFile;
  infoFile.setPath(m_currentInfoFile);
  infoFile.setId(ui->lineEditId->text());
  infoFile.setContent(ui->plainTextEditInformation->toPlainText());
  infoFile.writeToFile();
}

void MainWindow::on_pushButtonSwitch_clicked()
{
  QListWidgetItem* listWidgetItem = ui->listWidgetProjects->currentItem();

  if (!listWidgetItem)
  {
    qDebug() << tr("no item selected");
    return;
  }

  QString listWidgetItemText = listWidgetItem->text();

  if (listWidgetItemText == ui->lineEditBaseName->text())
  {
    showUserMessage(tr("no switch necessary"));
    return;
  }

  QString currentDirName = ui->lineEditBaseDirectory->text() + QDir::separator() + ui->lineEditBaseName->text();
  QString selectedDirName = ui->lineEditBaseDirectory->text() + QDir::separator() + listWidgetItemText;

  QDir currentDir(currentDirName);
  QDir selectedDir(selectedDirName);

  if (currentDir.exists())
  {
    InfoFile infoFile(currentDirName + QDir::separator() + m_infoFileName);

    QString newDirName = currentDirName + '_' + infoFile.id();

    if(!currentDir.rename(currentDirName, newDirName))
    {
      showUserMessage(tr("rename of current dir \n%1\nto\n%2\nwas not possible").arg(currentDirName).arg(newDirName));
      return;
    }
  }

  if (selectedDir.exists())
  {
    QString newDirName = ui->lineEditBaseDirectory->text() + QDir::separator() + ui->lineEditBaseName->text();
    if(!selectedDir.rename(selectedDirName, newDirName))
    {
      showUserMessage(tr("rename of selected dir\n%1\nto\n%2\nwas not possible").arg(selectedDirName).arg(newDirName));
      return;
    }
  }

  checkDirectory();
}

void MainWindow::on_pushButtonCreateNew_clicked()
{
  showUserMessage("ToDo");
}
