/* TODO
------------------------------
 * write some statistics to status bar?
 * Timea fragen, wie bisher das "Fehlerhandling" war. Was soll passieren, wenn der Artikel schon mal eingegeben wurde? Wie könnte man Fehler korrigieren?
 * Styling überarbeiten -> Schriftgrößen, Ausrichtung der GUI-Elemente
 * Scanner -> definieren, wie dieser eingestellt werden muss - Liste kopieren?
 * Sonderzeichen werden teilweise falsch dargestllt - Encoding von den Files kontrollieren und main verifzieren.
 * Ausdruck für Verkäufer erstellen -> void Evaluation::printEvaluation()
 */


/* Printing
 * print webview -> page break not possible
 * print QTextDocument -> styles are not fully taken, encoding does not fit
 * do printing by myself -> don't think, that this is a good idea!
 */


#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTextStream>
#include <QRegExp>
#include <QRegExpValidator>

#include "TuKiBasar.h"
#include "ui_TuKiBasar.h"

#include "Article.h"
#include "ArticleManager.h"
#include "Evaluation.h"
#include "Settings.h"
#include "PrizeCorrection.h"

TuKiBasar::TuKiBasar(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::TuKiBasar)
{
  ui->setupUi(this);

  QRegExp rx ("[0-9]{6}");
  ui->lineEditInput->setValidator(new QRegExpValidator (rx, this));

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

  prepareForNextInput();
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

  if (!conversion1 || !conversion2)
  {
    // should not happen, since we use a QRegExpValidator
    QMessageBox mb;
    mb.setText(tr("Die Eingabe ist fehlerhaft!"));
    mb.exec();
    ui->lineEditInput->selectAll();
    return;
  }

  if (sellerNumber > m_settings->getSellerMax())
  {
    QMessageBox mb;
    mb.setText(tr("Die eingegebene Verkäufernummer ist zu hoch!\nDas Maximum ist %1!").arg(m_settings->getSellerMax()));
    mb.exec();
    ui->lineEditInput->selectAll();
    return;
  }

  if (sellerNumber < m_settings->getSellerMin())
  {
    QMessageBox mb;
    mb.setText(tr("Die eingegebene Verkäufernummer ist zu niedrig!\nDas Minimum ist %1!").arg(m_settings->getSellerMin()));
    mb.exec();
    ui->lineEditInput->selectAll();
    return;
  }

  if (articleNumber > m_settings->getArticleMax())
  {
    QMessageBox mb;
    mb.setText(tr("Die eingegebene Artikelnummer ist zu hoch!\nDas Maximum ist %1!").arg(m_settings->getArticleMax()));
    mb.exec();
    ui->lineEditInput->selectAll();
    return;
  }

  if (articleNumber < m_settings->getArticleMin())
  {
    QMessageBox mb;
    mb.setText(tr("Die eingegebene Artikelnummer ist zu niedrig!\nDas Minimum ist %1!").arg(m_settings->getArticleMin()));
    mb.exec();
    ui->lineEditInput->selectAll();
    return;
  }

  if (m_articleManager->isArticleInCurrentSale(sellerNumber, articleNumber))
  {
    QMessageBox mb;
    mb.setText(tr("Der eingegebene Artikel ist bereits in der aktuellen Artikelliste enthalten!"));
    mb.exec();
    ui->lineEditInput->selectAll();
    return;
  }

  Article* article = m_articleManager->getArticle(sellerNumber, articleNumber);

  bool prizeCorrectionRequired = false;
  if (article != 0)
  {
    if (article->m_soldOnPc != 0)
    {
      QMessageBox mb;
      mb.setText(tr("Der eingegebene Artikel wurde bereits verkauft!"));
      mb.exec();
      ui->lineEditInput->selectAll();
      return;
    }

    m_articleManager->addArticleToCurrentSale(article);
  }
  else
  {
    Article* newArticle = new Article(articleNumber, sellerNumber, 0, 0.0, "", "", "");
    m_articleManager->addArticle(newArticle);
    m_articleManager->addArticleToCurrentSale(newArticle);

    QMessageBox mb;
    mb.setText(tr("Der eingegebene Artikel ist im System nicht hinterlegt.\nBitte Preis manuell eingeben!"));
    mb.exec();
    prizeCorrectionRequired = true;
  }

  setLastArticleInformation();
  updateArticleView();

  ui->lineEditInput->clear();

  if (prizeCorrectionRequired)
  {
    on_pushButtonCorrectPrize_clicked();
  }
}

void TuKiBasar::on_pushButtonDeleteLastInput_clicked()
{
  m_articleManager->removeLastArticleFromCurrentSale();
  Article* article = m_articleManager->getLastArticleInCurrentSale();

  if (article != 0)
  {
    setLastArticleInformation();
  }
  else
  {
    clearLastArticleInformation();
  }

  updateArticleView();
  prepareForNextInput();
}

void TuKiBasar::setLastArticleInformation()
{
  Article *article = m_articleManager->getLastArticleInCurrentSale();

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

void TuKiBasar::prepareForNextInput()
{
  ui->lineEditInput->clear();
  ui->lineEditInput->setFocus();
}

void TuKiBasar::on_pushButtonNextCustomer_clicked()
{
  m_articleManager->finishCurrentSale(m_settings->getPc());
  clearLastArticleInformation();
  updateArticleView();
  prepareForNextInput();
}

void TuKiBasar::on_actionCompleteEvaluation_triggered()
{
  askUserToFinishCurrentSale();

  QStringList files = QFileDialog::getOpenFileNames(this, "Bitte Dateien auswählen", "", "XML-Dateien (*.xml)");

  if (files.empty())
  {
    return;
  }

  ArticleManager* totalArticleManager = new ArticleManager(m_settings, files.at(0));

  for (int i = 1; i < files.length(); i++)
  {
    ArticleManager* articleManagerToSync = new ArticleManager(m_settings, files.at(i));
    totalArticleManager->sync(articleManagerToSync);
    delete articleManagerToSync;
  }

  Evaluation* totalEvaluation = new Evaluation(totalArticleManager);
  totalEvaluation->doEvaluation();
  totalEvaluation->setPrintButtonVisible(true);
  totalEvaluation->exec();

  delete totalEvaluation;
  delete totalArticleManager;

  prepareForNextInput();
}

void TuKiBasar::on_pushButtonCorrectPrize_clicked()
{
  Article* article = m_articleManager->getLastArticleInCurrentSale();

  if (article == 0)
  {
    prepareForNextInput();
    return;
  }

  PrizeCorrection prizeCorrection;
  prizeCorrection.setPrize(article->m_prize);
  if (prizeCorrection.exec() == QDialog::Accepted)
  {
    article->m_prize = prizeCorrection.getPrize();
  }

  updateArticleView();
  setLastArticleInformation();
  prepareForNextInput();
}

void TuKiBasar::closeEvent(QCloseEvent *event)
{
  askUserToFinishCurrentSale();

  event->accept();
}
