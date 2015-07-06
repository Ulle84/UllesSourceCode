#include <QSettings>

#include "DevelopmentHelper.h"
#include "ui_DevelopmentHelper.h"

#include "StashHelper.h"
#include "LogFileViewer.h"

DevelopmentHelper::DevelopmentHelper(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DevelopmentHelper)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "DevelopmentHelper", this);

  m_stashHelper = new StashHelper(this);
  m_logFileViewer = new LogFileViewer(this);

  ui->tabWidget->addTab(m_stashHelper, "Stash");
  ui->tabWidget->addTab(m_logFileViewer, "Log File Viewer");

  if (m_settings->contains("activeTabNumber"))
  {
    ui->tabWidget->setCurrentIndex(m_settings->value("activeTabNumber").toInt());
  }
}

DevelopmentHelper::~DevelopmentHelper()
{
  m_settings->setValue("activeTabNumber", ui->tabWidget->currentIndex());
  delete ui;
}
