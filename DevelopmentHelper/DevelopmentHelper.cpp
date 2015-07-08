#include <QSettings>

#include "DevelopmentHelper.h"
#include "ui_DevelopmentHelper.h"

#include "CodeAssistant.h"
#include "ConverterBase64.h"
#include "DateTimeHelper.h"
#include "HtmlTableGenerator.h"
#include "LogFileViewer.h"
#include "StashHelper.h"
#include "CryptoHelper.h"
#include "ClipboardManager.h"
#include "ColorPicker.h"
#include "RequireFileHelper.h"
#include "RegExpTester.h"

DevelopmentHelper::DevelopmentHelper(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DevelopmentHelper),
  m_currentIndex(-1)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "DevelopmentHelper", this);

  m_widgets["Stash"] = new StashHelper(this);
  m_widgets["Log File Viewer"] = new LogFileViewer(this);
  m_widgets["Code Assistant"] = new CodeAssistant(this);
  m_widgets["Converter Base64"] = new ConverterBase64(this);
  m_widgets["Date and Time Helper"] = new DateTimeHelper(this);
  m_widgets["HTML Table Generator"] = new HtmlTableGenerator(this);
  m_widgets["Crypto Helper"] = new CryptoHelper(this);
  m_widgets["Clipboard Manager"] = new ClipboardManager(this);
  m_widgets["Color Picker"] = new ColorPicker(this);
  m_widgets["Require File Helper"] = new RequireFileHelper(this);
  m_widgets["RegExp Tester"] = new RegExpTester(this);

  bool firstWidget = true;
  for (auto it = m_widgets.begin(); it != m_widgets.end(); it++)
  {
    ui->comboBox->addItem(it.key());
    ui->centralWidget->layout()->addWidget(it.value());
    it.value()->setVisible(firstWidget);
    firstWidget = false;
  }

  if (m_settings->contains("activeTabNumber"))
  {
    ui->comboBox->setCurrentIndex(m_settings->value("activeTabNumber").toInt());
  }

  if (m_settings->contains("windowGeometry"))
  {
    this->setGeometry(m_settings->value("windowGeometry").toRect());
  }
}

DevelopmentHelper::~DevelopmentHelper()
{
  m_settings->setValue("windowGeometry", this->geometry());
  m_settings->setValue("activeTabNumber", ui->comboBox->currentIndex());
  delete ui;
}

void DevelopmentHelper::on_comboBox_currentIndexChanged(int index)
{
  setWidgetVisible(index);
}

void DevelopmentHelper::setWidgetVisible(int index)
{
  int counter = 0;
  for (auto it = m_widgets.begin(); it != m_widgets.end(); it++)
  {
    if (counter == m_currentIndex)
    {
      it.value()->setVisible(false);
    }

    if (counter == index)
    {
      it.value()->setVisible(true);
    }

    counter++;
  }
  m_currentIndex = index;
}
