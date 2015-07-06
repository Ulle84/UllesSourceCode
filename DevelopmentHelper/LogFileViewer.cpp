#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtAlgorithms>
#include <QRegExp>
#include <QSettings>
#include <QStringList>
#include <QTextStream>


#include "LogFileViewer.h"
#include "ui_LogFileViewer.h"

const int g_dateStringLength = 23;

bool compareLogStrings(const QString& s1, const QString& s2)
{
  // 2015-05-27 15:58:38,306
  return s1.left(g_dateStringLength) < s2.left(g_dateStringLength);
}

LogFileViewer::LogFileViewer(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LogFileViewer)
{
  ui->setupUi(this);

  m_settings = new QSettings("company.com", "LogFileViewer", this);

    if (m_settings->contains("dir"))
    {
      m_dir.setPath(m_settings->value("dir").toString());
    }
    else
    {
      m_dir = QDir::current();
    }

    m_regExp = new QRegExp("\\d{4,4}-\\d{2,2}-\\d{2,2} \\d{2,2}:\\d{2,2}:\\d{2,2},\\d{3,3}");
}

LogFileViewer::~LogFileViewer()
{
  delete m_regExp;
  delete ui;
}

void LogFileViewer::on_pushButtonOpenFiles_clicked()
{
  readFilesAndMerge();

  // display merged content
  ui->plainTextEdit->clear();
  ui->plainTextEdit->appendPlainText(m_mergedFileContent.join(""));
}

void LogFileViewer::on_pushButtonCombineFiles_clicked()
{
  if (!readFilesAndMerge())
  {
    return;
  }

  QString fileNameSuggestion = m_dir.absolutePath() + "/_combinedLogFile.log";

  QString fileName = QFileDialog::getSaveFileName(this, tr("Please choose log-file destination"), fileNameSuggestion, QString("%1 (*.*)").arg(tr("log file")));

  if (fileName.isEmpty())
  {
    return;
  }

  updateDir(fileName);

  QFile file(fileName);
  QTextStream stream(&file);

  if (file.open(QIODevice::ReadWrite))
  {
    for (auto it = m_mergedFileContent.begin(); it != m_mergedFileContent.end(); it++)
    {
      stream << *it;
    }
  }

  QMessageBox::information(this, tr("Success"), tr("File has been written successfully"));
}

bool LogFileViewer::readFilesAndMerge()
{
  QStringList files = QFileDialog::getOpenFileNames(this, tr("Please choose log-files"), m_dir.absolutePath(), QString("%1 (*.*)").arg(tr("log files")));

  if (files.length() < 1)
  {
    ui->plainTextEdit->clear();
    return false;
  }

  m_mergedFileContent.clear();

  updateDir(files.at(0));

  for (int i = 0; i < files.length(); i++)
  {
    readFile(files.at(i));
  }

  qStableSort(m_mergedFileContent.begin(), m_mergedFileContent.end(), compareLogStrings);

  return true;
}

void LogFileViewer::updateDir(const QString &fileName)
{
  m_dir.setPath(fileName);
  m_dir.cdUp();
  m_settings->setValue("dir", m_dir.absolutePath());
}

bool LogFileViewer::readFile(const QString &fileName)
{
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    return false;
  }

  bool firstLine = true;
  while (!file.atEnd())
  {
    QByteArray line = file.readLine();

    if (line.trimmed().isEmpty())
    {
      firstLine = false;
      continue;
    }

    if (m_regExp->exactMatch(line.left(g_dateStringLength)))
    {
      m_mergedFileContent.append(line);
    }
    else
    {
      if (m_mergedFileContent.length() > 0 && !firstLine)
      {
        m_mergedFileContent.last().append(line);
      }
    }
    firstLine = false;
  }

  return true;
}
