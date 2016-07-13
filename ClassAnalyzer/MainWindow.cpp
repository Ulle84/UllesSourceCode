#include <QFileDialog>
#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "ClassAnalyzer", this);

  if (m_settings->contains("lastSelectedDirectory"))
  {
    m_lastSelectedDirectory = m_settings->value("lastSelectedDirectory").toString();
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("lastSelectedDirectory", m_lastSelectedDirectory);
  delete ui;
}

void MainWindow::on_pushButtonParseFolder_clicked()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Select folder.."), m_lastSelectedDirectory);

  if (directory.isEmpty())
  {
    return;
  }

  m_lastSelectedDirectory = directory;

  m_classAnalyzer.parseFolder(directory);
}
