#include <QSettings>
#include <QUiLoader>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowTitle("GUI Style Tester");

  m_settings = new QSettings("Ulle", "GuiStyleTester", this);

  ui->cssSelector->setPath(m_settings->value("cssPath").toString());
  ui->uiSelector->setPath(m_settings->value("uiPath").toString());

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("cssPath", ui->cssSelector->path());
  m_settings->setValue("uiPath", ui->uiSelector->path());

  delete ui;
}

void MainWindow::on_pushButtonApplyUi_clicked()
{
  QLayoutItem *child;
  while ((child = ui->verticalLayoutUi->takeAt(0)) != 0)
  {
    delete child->widget();
    delete child;
  }

  QFile uiFile(ui->uiSelector->path());

  if (!uiFile.exists())
  {
    return;
  }

  if (!uiFile.open(QFile::ReadOnly))
  {
    return;
  }

  QUiLoader loader;
  QWidget *widget = loader.load(&uiFile, this);
  uiFile.close();
  ui->verticalLayoutUi->addWidget(widget);

}

void MainWindow::on_pushButtonApplyCss_clicked()
{
  applyCss();

  if (!m_timer)
  {
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::checkFiles);
    m_timer->start(1000);
  }
}

void MainWindow::checkFiles()
{
  QFile file(ui->cssSelector->path());

  if (!file.exists())
  {
    return;
  }

  QFileInfo fileInfo(ui->cssSelector->path());

  if (fileInfo.lastModified() != m_cssLastModified)
  {
    applyCss();
  }
}

void MainWindow::applyCss()
{
  QFile file(ui->cssSelector->path());

  if (!file.exists())
  {
    return;
  }

  if (!file.open(QFile::ReadOnly))
  {
    return;
  }

  QFileInfo fileInfo(ui->cssSelector->path());
  m_cssLastModified = fileInfo.lastModified();

  qApp->setStyleSheet(file.readAll());
}
