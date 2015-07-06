#include "StashHelper.h"
#include "ui_StashHelper.h"

#include <QClipboard>

StashHelper::StashHelper(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StashHelper)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "DevelopmentHelper.StashHelper", this);

  m_projectCodes["Base"]             = "base";
  m_projectCodes["ViAcquisition"]    = "viacq";
  m_projectCodes["ViObjects"]        = "viob";
  m_projectCodes["ViObjectsMethods"] = "vimeth";
  m_projectCodes["ViQtWidgets"]      = "viqtwdgt";
  m_projectCodes["ViWidgets"]        = "viwdgt";

  for (auto it = m_projectCodes.begin(); it != m_projectCodes.end(); it++)
  {
   ui->comboBoxProject->addItem(it.key());
  }

  if (m_settings->contains("project"))
  {
    ui->comboBoxProject->setCurrentIndex(ui->comboBoxProject->findText(m_settings->value("project").toString()));
  }
  if (m_settings->contains("repository"))
  {
    ui->lineEditRepository->setText(m_settings->value("repository").toString());
  }
}

StashHelper::~StashHelper()
{
  m_settings->setValue("project", ui->comboBoxProject->currentText());
  m_settings->setValue("repository", ui->lineEditRepository->text());

  delete ui;
}

void StashHelper::on_lineEditRepository_textEdited(const QString &repository)
{
  setStashUrl();
}


/*
Base             - IndDynTranslator        -> http://ube@stash.vitronic.de:7990/scm/base/inddyntranslator.git
ViAcquisition    - ViAcquiDocumentation    -> http://ube@stash.vitronic.de:7990/scm/viacq/viacquidocumentation.git
ViObjects        - ViObjectsBasis          -> http://ube@stash.vitronic.de:7990/scm/viob/viobjectsbasis.git
ViObjectsMethods - ViMethArray2DClassifier -> http://ube@stash.vitronic.de:7990/scm/vimeth/vimetharray2dclassifier.git
ViQtWidgets      - ViQtWidgetAbout         -> http://ube@stash.vitronic.de:7990/scm/viqtwdgt/viqtwidgetabout.git
ViWidgets        - ViAboutWidget           -> http://ube@stash.vitronic.de:7990/scm/viwdgt/viaboutwidget.git
*/

void StashHelper::on_comboBoxProject_currentIndexChanged(const QString &project)
{
  setStashUrl();
}

void StashHelper::setStashUrl()
{
  QString stashUrl = "http://ube@stash.vitronic.de:7990/scm/";
  stashUrl.append(m_projectCodes[ui->comboBoxProject->currentText()]);
  stashUrl.append("/");
  stashUrl.append(ui->lineEditRepository->text().toLower());
  stashUrl.append(".git");

  ui->lineEditStashUrl->setText(stashUrl);
}

void StashHelper::on_pushButtonRepositoryToClipoard_clicked()
{
    QApplication::clipboard()->setText(ui->lineEditRepository->text());
}

void StashHelper::on_pushButtonStashUrlToClipboard_clicked()
{
    QApplication::clipboard()->setText(ui->lineEditStashUrl->text());
}
