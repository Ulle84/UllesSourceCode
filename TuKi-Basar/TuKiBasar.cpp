/* TODO
------------------------------
 * Total Evaluation
 * Correct Prize Feature
 * Meldungen bei Falscher Eingabe
 * write some statistics to status bar
 * beim schliessen nachfragen, ob der letzte Verkauf noch abgeschlossen werden soll -> call function askuserToFinishcurrentsale
 */


#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTextStream>

#include "TuKiBasar.h"
#include "ui_TuKiBasar.h"

#include "Article.h"
#include "ArticleManager.h"
#include "Evaluation.h"
#include "Settings.h"

TuKiBasar::TuKiBasar(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::TuKiBasar)
{
  ui->setupUi(this);

  m_settings = new Settings();
  m_articleManager = new ArticleManager(m_settings, "Articles.xml");
  m_evaluation = new Evaluation(m_articleManager);


  // font depends on operating system
#ifdef Q_WS_MAC
  ui->plainTextEditArticleList->setFont(QFont::QFont("Monaco", 14, 0, false));
#endif
#ifdef Q_WS_WIN
  ui->plainTextEditArticleList->setFont(QFont::QFont("Courier", 10, 0, false));
#endif
}

TuKiBasar::~TuKiBasar()
{
  delete m_evaluation;

  m_articleManager->toXml();
  delete m_articleManager;

  delete m_settings;

  delete ui;
}

void TuKiBasar::on_actionSettings_triggered()
{
  m_settings->exec();
}

void TuKiBasar::on_actionEvaluation_triggered()
{
  askUserToFinishCurrentSale();

  m_evaluation->doEvaluation();
  m_evaluation->exec();
}

void TuKiBasar::on_actionImportArticleLists_triggered()
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, tr("Vorhandene Artikel löschen?"),
                                tr("Möchten Sie die bereits importierten Artikel löschen?"),
                                QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    m_articleManager->clear();
  }

  QString dirName = QFileDialog::getExistingDirectory(this, tr("Bitte Ordner mit den Artikellisten wählen...")); //TODO set folder of last selection?

  if (dirName.isEmpty())
  {
    return;
  }

  QDir dir(dirName);

  QStringList filters;
  filters << "articleList_*.txt";
  dir.setNameFilters(filters);

  QStringList fileNames = dir.entryList();

  unsigned int sellerCounter = 0;
  unsigned int articleCounter = 0;

  const int headerOffset = 3;
  const int linesPerArticle = 4;

  for (int i = 0; i < fileNames.length(); i++)
  {
    QString filePath = dir.filePath(fileNames.at(i));

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      continue;
    }

    QStringList fileContent;
    QTextStream in(&file);
    while (!in.atEnd())
    {
      fileContent.append(in.readLine());
    }

    if (fileContent.length() < headerOffset)
    {
      file.close();
      continue;
    }

    if (fileContent.at(0) != "Article List")
    {
      file.close();
      continue;
    }

    if ((fileContent.length() - headerOffset) % linesPerArticle != 0)
    {
      file.close();
      continue;
    }

    //TODO use version information if nessessary

    bool conversionSellerNumber;
    int sellerNumber = fileContent.at(2).toInt(&conversionSellerNumber);

    if (!conversionSellerNumber)
    {
      file.close();
      continue;
    }

    int numberOfArticles = (fileContent.length() - headerOffset) / linesPerArticle;

    for (int i = 0; i < numberOfArticles; i++)
    {
      bool conversionPrize;
      double prize = fileContent.value(headerOffset + linesPerArticle * i + 1).replace(",", ".").toDouble(&conversionPrize);
      if (!conversionPrize)
      {
        continue;
      }

      int articleNumber = fileContent.at(headerOffset + linesPerArticle * i).toInt();
      QString size = fileContent.at(headerOffset + linesPerArticle * i + 2);
      QString description = fileContent.at(headerOffset + linesPerArticle * i + 3);

      Article* article = new Article(articleNumber, sellerNumber, 0, prize, size, description, "");
      m_articleManager->addArticle(article); //TODO check that no article is added twice

      articleCounter++;
    }

    file.close();
    sellerCounter++;
  }

  m_articleManager->toXml();

  QMessageBox mb;
  if (articleCounter > 0)
  {
    mb.setText(tr("Es wurden erfolgreich %1 Artikel von %2 Verkäufern importiert.").arg(articleCounter).arg(sellerCounter));
  }
  else
  {
    mb.setText(tr("Es wurden keine Artikel importiert."));
  }

  mb.exec();
}

void TuKiBasar::on_lineEditInput_returnPressed()
{
  QString input = ui->lineEditInput->text();

  bool conversion1 = false;
  bool conversion2 = false;

  int sellerNumber = input.left(3).toInt(&conversion1);
  int articleNumber = input.right(3).toInt(&conversion2);

  ui->lineEditInput->clear();
  if (!conversion1 || !conversion2)
  {
    return;
  }

  Article* article = m_articleManager->getArticle(sellerNumber, articleNumber);

  if (article != 0)
  {
    setLastArticleInformation(article);

    m_articleManager->addArticleToCurrentSale(article);

    updateArticleView();
  }
}

void TuKiBasar::on_pushButtonDeleteLastInput_clicked()
{
  m_articleManager->removeLastArticleFromCurrentSale();
  Article* article = m_articleManager->getLastArticleInCurrentSale();

  if (article != 0)
  {
    setLastArticleInformation(article);
  }
  else
  {
    clearLastArticleInformation();
  }

  updateArticleView();
}

void TuKiBasar::setLastArticleInformation(Article *article)
{
  ui->labelArticleNumber->setText(QString("%1").arg(article->m_articleNumber));
  ui->labelSellerNumber->setText(QString("%1").arg(article->m_sellerNumber));
  ui->labelDescription->setText(article->m_description);
  ui->labelPrize->setText(m_articleManager->prizeToString(article->m_prize));
}

void TuKiBasar::clearLastArticleInformation()
{
  ui->labelArticleNumber->clear();
  ui->labelSellerNumber->clear();
  ui->labelDescription->clear();
  ui->labelPrize->clear();
}

void TuKiBasar::updateArticleView()
{
  ui->plainTextEditArticleList->setPlainText(m_articleManager->currentSaleToText());
}

void TuKiBasar::askUserToFinishCurrentSale()
{
  if(m_articleManager->isCurrentSaleEmpty())
  {
    return;
  }

  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, tr("Aktuellen Verkauf abschließen?"),
                                tr("Möchten Sie erst den aktuellen Verkauf abschließen?"),
                                QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    on_pushButtonNextCustomer_clicked();
  }
}

void TuKiBasar::on_pushButtonNextCustomer_clicked()
{
  m_articleManager->finishCurrentSale(m_settings->getPc());
  clearLastArticleInformation();
  updateArticleView();
}

void TuKiBasar::on_actionCompleteEvaluation_triggered()
{
  askUserToFinishCurrentSale();

  /*QString dirName = QFileDialog::getExistingDirectory(this, tr("Bitte Ordner mit den Artikellisten wählen...")); //TODO set folder of last selection?

  if (dirName.isEmpty())
  {
    return;
  }*/

  QStringList files = QFileDialog::getOpenFileNames(this, "Bitte Dateien auswählen", "", "XML-Dateien (*.xml)");

  if (files.empty())
  {
    return;
  }

  ArticleManager* totalArticleManager = new ArticleManager(m_settings, files.at(0));

  for (int i = 1; i < files.length(); i++)
  {
    ArticleManager* articleManagerToSync = new ArticleManager(m_settings, files.at(0));

    delete articleManagerToSync;
  }

  // sync all following files

  // doEvaluation
  Evaluation* totalEvaluation = new Evaluation(totalArticleManager);
  totalEvaluation->doEvaluation();
  totalEvaluation->exec();

  // show result of evaluation

  // clean up
  delete totalEvaluation;
  delete totalArticleManager;
}
