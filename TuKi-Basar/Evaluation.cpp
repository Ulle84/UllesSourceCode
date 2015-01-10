#include "Evaluation.h"
#include "ui_Evaluation.h"

#include <map>

#include <QPrinter>
#include <QWebFrame>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QTextDocument>
#include <QFileDialog>

#include "ArticleManager.h"
#include "Settings.h"

Evaluation::Evaluation(ArticleManager* articleManager, Settings *settings, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Evaluation),
  m_articleManager(articleManager),
  m_settings(settings)
{
  ui->setupUi(this);
  ui->webViewOverview->setVisible(false);
  ui->webViewSoldArticles->setVisible(false);
}

Evaluation::~Evaluation()
{
  delete ui;
}

void Evaluation::doEvaluation()
{
  m_articleManager->calculateStatistics(&m_volumeOfSale, &m_deduction, &m_deductionPercentage, &m_countOfSales, &m_countOfSoldArticles, &m_articlesPerSale, &m_countOfAllArticles, &m_percentageOfSoldArticles);

  m_volumeOfSaleString = QString("%1 Euro").arg(QString::number(m_volumeOfSale, 'f', 2).replace('.', ','));
  m_deductionString = QString("%1 Euro").arg(QString::number(m_deduction, 'f', 2).replace('.', ','));
  m_deductionDisplayString = tr("Einbehalt (%1 Prozent des Umsatzes)").arg(m_deductionPercentage);
  m_countOfSalesString = QString("%1").arg(m_countOfSales);
  m_countOfSoldArticlesString = QString("%1").arg(m_countOfSoldArticles);
  m_articlesPerSaleString = QString::number(m_articlesPerSale, 'f', 1).replace('.', ',');
  m_countOfAllArticlesString = QString("%1").arg(m_countOfAllArticles);
  m_percentageOfSoldArticlesString = QString("%1 Prozent").arg(QString::number(m_percentageOfSoldArticles, 'f', 1).replace('.', ','));

  ui->labelVolumeOfSale->setText(m_volumeOfSaleString);
  ui->labelDeduction->setText(m_deductionString);
  ui->labelDecuctionDisplay->setText(m_deductionDisplayString);
  ui->labelCountOfSales->setText(m_countOfSalesString);
  ui->labelCountOfSoldArticles->setText(m_countOfSoldArticlesString);
  ui->labelArticlesPerSale->setText(m_articlesPerSaleString);
  ui->labelCountOfAllArticles->setText(m_countOfAllArticlesString);
  ui->labelPercentageOfSoldArticles->setText(m_percentageOfSoldArticlesString);

  updateWebViews();
}

void Evaluation::saveOverview()
{
  QString outputFile = QFileDialog::getSaveFileName(this, tr("Bitte geben Sie den Dateinamen an"), QString("%1.pdf").arg(tr("Gesamtauswertung")), QString("PDF-%1 (*.pdf)").arg(tr("Datei")));

  if (outputFile.isEmpty())
  {
    return;
  }

  QPrinter printer(QPrinter::HighResolution); //HighResolution
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setPageSize(QPrinter::A4);
  int margin = 5;
  printer.setPageMargins(margin, margin, margin, margin, QPrinter::Millimeter);
  printer.setColorMode(QPrinter::GrayScale);
  printer.setOutputFileName(outputFile);

  ui->webViewOverview->page()->mainFrame()->print(&printer);

  if (ui->checkBoxOpenOverview->isChecked())
  {
    // show pdf with external viewer
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir(outputFile).absolutePath()));
  }
}

void Evaluation::saveSoldArticles()
{
  QString outputFile = QFileDialog::getSaveFileName(this, tr("Bitte geben Sie den Dateinamen an"), QString("%1.pdf").arg(tr("Verkäuferübersicht")), QString("PDF-%1 (*.pdf)").arg(tr("Datei")));

  if (outputFile.isEmpty())
  {
    return;
  }

  QPrinter printer(QPrinter::HighResolution); //HighResolution
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setPageSize(QPrinter::A4);
  int margin = 5;
  printer.setPageMargins(margin, margin, margin, margin, QPrinter::Millimeter);
  printer.setColorMode(QPrinter::GrayScale);
  printer.setOutputFileName(outputFile);

  ui->webViewSoldArticles->page()->mainFrame()->print(&printer);

  if (ui->checkBoxOpenSoldArticles->isChecked())
  {
    // show pdf with external viewer
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir(outputFile).absolutePath()));
  }
}

void Evaluation::on_pushButtonSaveOverview_clicked()
{
  saveOverview();
}

void Evaluation::on_pushButtonSaveSoldArticles_clicked()
{
  saveSoldArticles();
}

void Evaluation::on_webViewOverview_loadFinished(bool loadFinished)
{
  if (!loadFinished)
  {
    return;
  }
  ui->pushButtonSaveOverview->setEnabled(true);
}

void Evaluation::on_webViewSoldArticles_loadFinished(bool loadFinished)
{
  if (!loadFinished)
  {
    return;
  }
  ui->pushButtonSaveSoldArticles->setEnabled(true);
}

void Evaluation::updateWebViews()
{
  ui->webViewOverview->setContent(createHtmlCodeOverview());
  ui->webViewSoldArticles->setContent(createHtmlCodeSoldArticles());
}

QByteArray Evaluation::createHtmlCodeOverview()
{
  QByteArray html;
  html.append("<!DOCTYPE html>");
  html.append("<html><head>");
  html.append("<meta charset=\"utf-8\">");
  html.append("<title></title></head><body>");
  html.append("<h1>Zusammenfassung</h1>");
  html.append("<table>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(ui->labelVolumeOfSaleDisplay->text()));
  html.append(QString("<td>%1</td>").arg(m_volumeOfSaleString));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(m_deductionDisplayString));
  html.append(QString("<td>%1</td>").arg(m_deductionString));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(ui->labelCountOfSalesDisplay->text()));
  html.append(QString("<td>%1</td>").arg(m_countOfSalesString));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(ui->labelCountOfSoldArticlesDisplay->text()));
  html.append(QString("<td>%1</td>").arg(m_countOfSoldArticlesString));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(ui->labelArticlesPerSaleDisplay->text()));
  html.append(QString("<td>%1</td>").arg(m_articlesPerSaleString));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(ui->labelCountOfAllArticlesDisplay->text()));
  html.append(QString("<td>%1</td>").arg(m_countOfAllArticlesString));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(ui->labelPercentageOfSoldArticlesDisplay->text()));
  html.append(QString("<td>%1</td>").arg(m_percentageOfSoldArticlesString));
  html.append("</tr>");
  html.append("</table>");
  html.append("<table>");
  html.append("<tr>");
  html.append("<th>Verkäufernummer</th>");
  html.append("<th>Summe</th>");
  html.append("<th>Auszuzahlen</th>");
  html.append("</tr>");

  std::map<int, double> matrix = m_articleManager->getSellerMatrix();
  double payOutFactor = m_articleManager->getPayOutFactor();

  for (auto it = matrix.begin(); it != matrix.end(); ++it)
  {
    html.append("<tr>");
    html.append(QString("<td>%1</td>").arg(it->first));
    html.append(QString("<td>%1 Euro</td>").arg(QString::number(it->second, 'f', 2).replace('.', ',')));
    html.append(QString("<td>%1 Euro</td>").arg(QString::number(it->second * payOutFactor, 'f', 2).replace('.', ',')));
    html.append("</tr>");
  }

  html.append("</body></html>");

  return html;
}

QByteArray Evaluation::createHtmlCodeSoldArticles()
{
  QByteArray html;
  html.append("<!DOCTYPE html>");
  html.append("<html><head>");
  html.append("<meta charset=\"utf-8\">");
  html.append("<style>");
  html.append("body, h1, html{margin: 0px; padding: 0px;}");
  html.append(".page{min-height: 26.85cm; max-height: 26.85cm; border-bottom: 1px solid black;}"); //TODO remove border
  html.append("</style>");
  html.append("<title></title></head><body>");

  std::map<int, double> matrix = m_articleManager->getSellerMatrix();
  double payOutFactor = m_articleManager->getPayOutFactor();

  for (auto it = matrix.begin(); it != matrix.end(); ++it)
  {
    std::map<int, double> articles = m_articleManager->getArticleMatrix(it->first);

    html.append("<div class=\"page\">");
    html.append(QString("<h1>Verkäufernummer %1</h1>").arg(it->first));
    html.append("<table>");
    html.append("<tr>");
    html.append(QString("<td>Umsatz</td>"));
    html.append(QString("<td>%1 Euro</td>").arg(QString::number(it->second, 'f', 2).replace('.', ',')));
    html.append("</tr>");
    html.append("<tr>");
    html.append(QString("<td>Einbehalt</td>"));
    html.append(QString("<td>%1 Euro</td>").arg(QString::number(it->second * (1.0 - payOutFactor), 'f', 2).replace('.', ',')));
    html.append("</tr>");
    html.append("<tr>");
    html.append(QString("<td><b>Auszahlbetrag</b></td>"));
    html.append(QString("<td><b>%1 Euro</b></td>").arg(QString::number(it->second * payOutFactor, 'f', 2).replace('.', ',')));
    html.append("</tr>");
    html.append("</table>");

    html.append("<h2>Liste der verkauften Artikel</h2>");
    html.append("<table>");

    for (auto itA = articles.begin(); itA != articles.end(); ++itA)
    {
      html.append("<tr>");
      html.append(QString("<td>%1</td>").arg(itA->first));
      html.append(QString("<td>%1 Euro</td>").arg(QString::number(itA->second, 'f', 2).replace('.', ',')));
      html.append("</tr>");
    }

    html.append("</table>");
    html.append("</div>");
  }

  html.append("</body></html>");

  return html;
}

