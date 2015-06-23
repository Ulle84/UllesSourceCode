#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QStringList>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QtAlgorithms>

bool compareLogStrings(const QString &s1, const QString &s2)
{
  // 2015-05-27 15:58:38,306
  return s1.left(23) < s2.left(23);
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButtonOpenFiles_clicked()
{
  QStringList files = QFileDialog::getOpenFileNames(this, tr("Please choose log-files"), "", QString("%1 (*.*)").arg(tr("log files")));

  if (files.length() < 1)
  {
    ui->plainTextEdit->clear();
    return;
  }

  QStringList mergedFileContent;

  // open first file and read content
  QFile file(files.at(0));
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    return;
  }

  while (!file.atEnd())
  {
    QByteArray line = file.readLine();
    mergedFileContent.append(line);
  }

  // open all other files and merge their content with current content
  if (files.length() > 1)
  {
    for (int i = 1; i < files.length(); i++)
    {
      QFile fileToMerge(files.at(i));
      if (!fileToMerge.open(QIODevice::ReadOnly | QIODevice::Text))
      {
        continue;
      }

      while (!fileToMerge.atEnd())
      {
        QByteArray lineToMerge = fileToMerge.readLine();
        mergedFileContent.append(lineToMerge);
      }
    }
  }

  qStableSort(mergedFileContent.begin(), mergedFileContent.end(), compareLogStrings);

  // display merged content
  ui->plainTextEdit->clear();
  ui->plainTextEdit->appendPlainText(mergedFileContent.join(""));
}
