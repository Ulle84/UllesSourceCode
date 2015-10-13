#include "BitbucketHelper.h"
#include "ui_BitbucketHelper.h"

#include <QClipboard>

BitbucketHelper::BitbucketHelper(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::BitbucketHelper)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "DevelopmentHelper.BitbucketHelper", this);

  m_projectCodes["Base"] = "base";
  m_projectCodes["IndVisualStudioTemplates"] = "invst";
  m_projectCodes["ViAcquisition"] = "viacq";
  m_projectCodes["ViIO"] = "viio";
  m_projectCodes["ViObjects"] = "viob";
  m_projectCodes["ViObjectsMethods"] = "vimeth";
  m_projectCodes["ViObjectsResults"] = "vires";
  m_projectCodes["ViQtWidgets"] = "viqtwdgt";
  m_projectCodes["ViWidgets"] = "viwdgt";

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

  setStashUrl();
}

BitbucketHelper::~BitbucketHelper()
{
  m_settings->setValue("project", ui->comboBoxProject->currentText());
  m_settings->setValue("repository", ui->lineEditRepository->text());

  delete ui;
}

void BitbucketHelper::on_lineEditRepository_returnPressed()
{
  QString repository = ui->lineEditRepository->text();

  if (repository.startsWith("ViQtWidget"))
  {
    ui->comboBoxProject->setCurrentIndex(ui->comboBoxProject->findText("ViQtWidgets"));
  }
  else if (repository.startsWith("Vi") && repository.endsWith("Widget"))
  {
    ui->comboBoxProject->setCurrentIndex(ui->comboBoxProject->findText("ViWidgets"));
  }
  else if (repository.startsWith("ViAcqui"))
  {
    ui->comboBoxProject->setCurrentIndex(ui->comboBoxProject->findText("ViAcquisition"));
  }
  else if (repository.startsWith("ViMeth"))
  {
    ui->comboBoxProject->setCurrentIndex(ui->comboBoxProject->findText("ViObjectsMethods"));
  }
  else if (repository.startsWith("ViIO"))
  {
    ui->comboBoxProject->setCurrentIndex(ui->comboBoxProject->findText("ViIO"));
  }
  else if (repository.startsWith("ViRes") || repository.startsWith("ViPLCRes"))
  {
    ui->comboBoxProject->setCurrentIndex(ui->comboBoxProject->findText("ViObjectsResults"));
  }

  setStashUrl();
}

void BitbucketHelper::on_comboBoxProject_currentIndexChanged(const QString& project)
{
  setStashUrl();
}

void BitbucketHelper::setStashUrl()
{
  QString stashUrl = "http://ube@stash.vitronic.de:7990/scm/";
  stashUrl.append(m_projectCodes[ui->comboBoxProject->currentText()]);
  stashUrl.append("/");
  stashUrl.append(ui->lineEditRepository->text().toLower());
  stashUrl.append(".git");

  ui->lineEditStashUrl->setText(stashUrl);
}

void BitbucketHelper::on_pushButtonRepositoryToClipoard_clicked()
{
  QApplication::clipboard()->setText(ui->lineEditRepository->text());
}

void BitbucketHelper::on_pushButtonStashUrlToClipboard_clicked()
{
  QApplication::clipboard()->setText(ui->lineEditStashUrl->text());
}
