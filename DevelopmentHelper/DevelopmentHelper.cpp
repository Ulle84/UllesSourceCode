#include <QSettings>

#include "DevelopmentHelper.h"
#include "ui_DevelopmentHelper.h"

#include "CodeAssistant.h"
#include "ConverterBase64.h"
#include "DateTimeHelper.h"
#include "LogFileViewer.h"
#include "StashHelper.h"

DevelopmentHelper::DevelopmentHelper(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DevelopmentHelper)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "DevelopmentHelper", this);

  m_stashHelper = new StashHelper(this);
  m_logFileViewer = new LogFileViewer(this);
  m_codeAssistant = new CodeAssistant(this);
  m_converterBase64 = new ConverterBase64(this);
  m_dateTimeHelper = new DateTimeHelper(this);

  ui->tabWidget->addTab(m_stashHelper, "Stash");
  ui->tabWidget->addTab(m_logFileViewer, tr("Log File Viewer"));
  ui->tabWidget->addTab(m_codeAssistant, tr("Code Assistant"));
  ui->tabWidget->addTab(m_converterBase64, tr("Converter Base 64"));
  ui->tabWidget->addTab(m_dateTimeHelper, tr("Date and Time"));

  if (m_settings->contains("activeTabNumber"))
  {
    ui->tabWidget->setCurrentIndex(m_settings->value("activeTabNumber").toInt());
  }

  if (m_settings->contains("windowGeometry"))
  {
    this->setGeometry(m_settings->value("windowGeometry").toRect());
  }
}

DevelopmentHelper::~DevelopmentHelper()
{
  m_settings->setValue("windowGeometry", this->geometry());
  m_settings->setValue("activeTabNumber", ui->tabWidget->currentIndex());
  delete ui;
}
