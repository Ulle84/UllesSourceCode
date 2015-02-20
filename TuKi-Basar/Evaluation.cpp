#include "Evaluation.h"
#include "ui_Evaluation.h"

#include <map>

#include <QPrinter>
#include <QWebFrame>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <QString>
#include <QTextDocument>
#include <QFileDialog>

#include "ArticleManager.h"
#include "Settings.h"
#include "Statistics.h"
#include "EvaluationView.h"
#include "Seller.h"
#include "SellerManager.h"

Evaluation::Evaluation(ArticleManager* articleManager, Settings *settings, SellerManager *sellerManager, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Evaluation),
  m_articleManager(articleManager),
  m_settings(settings),
  m_sellerManager(sellerManager)
{
  ui->setupUi(this);

  m_statistics = new Statistics();

  m_overview = new EvaluationView(tr("Gesamtübersicht"), this);
  m_soldArticles = new EvaluationView(tr("Verkaufte Artikel"), this);
  m_unsoldArticles = new EvaluationView(tr("Nicht verkaufte Artikel"), this);

  ui->tabWidget->addTab(m_overview, m_overview->getName());
  ui->tabWidget->addTab(m_soldArticles, m_soldArticles->getName());
  ui->tabWidget->addTab(m_unsoldArticles, m_unsoldArticles->getName());
}

Evaluation::~Evaluation()
{
  delete m_statistics;
  delete ui;
}

void Evaluation::doEvaluation()
{
  m_articleManager->calculateStatistics(m_statistics);
  updateWebViews();
}

void Evaluation::updateWebViews()
{
  m_overview->setHtmlContent(createHtmlCodeOverview());
  m_soldArticles->setHtmlContent(createHtmlCodeSoldArticles());
  m_unsoldArticles->setHtmlContent(createHtmlCodeUnsoldArticles());
}

QString Evaluation::createCssCode()
{
  QString cssCode;
  cssCode.append("<style>");
  cssCode.append("body, h1, html{margin: 0px; padding: 0px;}"); // TODO check compliance with further definitions
  cssCode.append("body {font-family: Verdana; font-size: 10pt; max-width: 800px; line-height: 150%;}");
  cssCode.append("br {margin-bottom: 12px;}");
  cssCode.append("h1 {margin-top: 20px; padding-top: 20px; font-size: 130%; padding-bottom: 5px; margin-bottom: 0px;}");
  cssCode.append("h2 {margin-top: 10px; padding-top: 10px; font-size: 120%; padding-bottom: 5px; margin-bottom: 0px;}");
  cssCode.append("h3 {margin-top: 7px; padding-top: 7px; font-size: 110%; padding-bottom: 5px; margin-bottom: 0px;}");
  cssCode.append("h4, h5, h6 {font-size: 105%; padding-bottom: 5px; margin-bottom: 0px;}");
  cssCode.append("table {border: 2px solid black; border-spacing: 0px;}");
  cssCode.append("table ul {margin-left: 20px; padding-left: 0px; margin-top: 0px; margin-bottom: 0px;}");
  //cssCode.append("tr:hover, tr:nth-child(even):hover, tr:nth-child(odd):hover {background-color: rgb(187, 188, 210);}");
  //cssCode.append("tr:nth-child(even) {background-color: rgb(230, 230, 230);}");
  //cssCode.append("tr:nth-child(odd) {background-color: rgb(255, 255, 255);}");
  cssCode.append("th {text-align: left;}");
  cssCode.append("td, th {max-width: 400px; padding: 5px 5px 5px 5px; vertical-align: top; border-bottom: 1px solid grey; border-right: 1px solid grey;}");
  cssCode.append("td:last-child, th:last-child {border-right: 0px;}");
  cssCode.append("tr:last-child > td {border-bottom: 0px;}");
  cssCode.append(".page{min-height: 26.85cm; max-height: 26.85cm; border-bottom: 1px solid black;}"); //TODO remove border
  cssCode.append("</style>");

  return cssCode;
}

QString Evaluation::createHtmlCodeOverview()
{
  QString html;
  html.append("<!DOCTYPE html>");
  html.append("<html><head>");
  html.append("<meta charset=\"utf-8\">");
  html.append("<title></title>");
  html.append(createCssCode());
  html.append("</head><body>");
  html.append("<h1>Zusammenfassung</h1>");
  html.append("<table>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(tr("Umsatz")));
  html.append(QString("<td>%1</td>").arg(QString("%1 Euro").arg(QString::number(m_statistics->m_volumeOfSale, 'f', 2).replace('.', ','))));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(tr("Einbehalt (%1 Prozent des Umsatzes)").arg(m_statistics->m_deductionPercentage)));
  html.append(QString("<td>%1</td>").arg(QString("%1 Euro").arg(QString::number(m_statistics->m_deduction, 'f', 2).replace('.', ','))));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(tr("Anzahl der Verkäufe")));
  html.append(QString("<td>%1</td>").arg(QString("%1").arg(m_statistics->m_countOfSales)));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(tr("Anzahl der verkauften Artikel")));
  html.append(QString("<td>%1</td>").arg(QString("%1").arg(m_statistics->m_countOfSoldArticles)));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(tr("Artikel pro Verkauf")));
  html.append(QString("<td>%1</td>").arg(QString::number(m_statistics->m_articlesPerSale, 'f', 1).replace('.', ',')));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(tr("Gesamtanzahl der Artikel")));
  html.append(QString("<td>%1</td>").arg(QString("%1").arg(m_statistics->m_countOfAllArticles)));
  html.append("</tr>");
  html.append("<tr>");
  html.append(QString("<td>%1</td>").arg(tr("Verkaufte Artikel")));
  html.append(QString("<td>%1</td>").arg(QString("%1 Prozent").arg(QString::number(m_statistics->m_percentageOfSoldArticles, 'f', 1).replace('.', ','))));
  html.append("</tr>");
  html.append("</table>");

  std::map<QString, int> offeredArticlesInRanges = m_articleManager->getOfferedArticlesInRanges();
  html.append("<h2>Anzahl der angebotenen Artikel</h2>");
  html.append("<table>");
  html.append("<tr>");
  html.append("<td>Angebotene Artikel</td>");
  html.append("<td>Anzahl Verkäufer</td>");
  html.append("</tr>");
  for (auto it = offeredArticlesInRanges.begin(); it != offeredArticlesInRanges.end(); ++it)
  {
    html.append("<tr>");
    html.append(QString("<td>%1</td>").arg(it->first));
    html.append(QString("<td>%1</td>").arg(it->second));
    html.append("</tr>");
  }
  html.append("</table>");

  std::map<QString, int> soldArticlesInRanges = m_articleManager->getSoldArticlesInRanges();
  html.append("<h2>Anzahl der verkauften Artikel</h2>");
  html.append("<table>");
  html.append("<tr>");
  html.append("<td>Verkauft Artikel</td>");
  html.append("<td>Anzahl Verkäufer</td>");
  html.append("</tr>");
  for (auto it = soldArticlesInRanges.begin(); it != soldArticlesInRanges.end(); ++it)
  {
    html.append("<tr>");
    html.append(QString("<td>%1</td>").arg(it->first));
    html.append(QString("<td>%1</td>").arg(it->second));
    html.append("</tr>");
  }
  html.append("</table>");

  html.append("<table>");
  html.append("<tr>");
  html.append("<th>Verkäufernummer</th>");
  html.append("<th>Summe</th>");
  html.append("<th>Auszuzahlen</th>");
  html.append("</tr>");

  std::map<int, double> matrix = m_articleManager->getSalesPerSeller();
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

QString Evaluation::createHtmlCodeSoldArticles()
{
  QString html;
  html.append("<!DOCTYPE html>");
  html.append("<html><head>");
  html.append("<title></title>");
  html.append(createCssCode());
  html.append("</head><body>");

  std::map<int, double> matrix = m_articleManager->getSalesPerSeller();
  double payOutFactor = m_articleManager->getPayOutFactor();

  for (auto it = matrix.begin(); it != matrix.end(); ++it)
  {
    std::map<int, double> articles = m_articleManager->getSoldArticles(it->first);

    Seller* seller = m_sellerManager->getSeller(it->first);

    html.append("<div class=\"page\">");
    if (seller != 0)
    {
      html.append(QString("<h1>Verkäufernummer: %1   Name: %2 %3   Telefon: %4</h1>").arg(it->first).arg(seller->m_firstName).arg(seller->m_lastName).arg(seller->m_phone));
    }
    else
    {
      html.append(QString("<h1>Verkäufernummer: %1").arg(it->first));
    }

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
    html.append("<tr>");
    html.append("<th>Artikelnummer</th>");
    html.append("<th>Preis</th>");
    html.append("<th>Größe</th>");
    html.append("<th>Artikelbeschreibung</th>");
    html.append("</tr>");

    for (auto itA = articles.begin(); itA != articles.end(); ++itA)
    {
      Article* article = m_articleManager->getArticle(it->first, itA->first);

      html.append("<tr>");
      html.append(QString("<td>%1</td>").arg(itA->first));
      html.append(QString("<td>%1 Euro</td>").arg(QString::number(itA->second, 'f', 2).replace('.', ',')));
      html.append(QString("<td>%1</td>").arg(article->m_size));
      html.append(QString("<td>%1</td>").arg(article->m_description));
      html.append("</tr>");
    }

    html.append("</table>");
    html.append("</div>");
  }

  html.append("</body></html>");

  return html;
}

QString Evaluation::createHtmlCodeUnsoldArticles()
{
  QString html;
  html.append("<!DOCTYPE html>");
  html.append("<html><head>");
  html.append("<meta charset=\"utf-8\">");
  html.append("<title></title>");
  html.append(createCssCode());
  html.append("</head><body>");

  std::map<int, double> matrix = m_articleManager->getSalesPerSeller();

  for (auto it = matrix.begin(); it != matrix.end(); ++it)
  {
    std::map<int, double> unsoldArticles = m_articleManager->getUnsoldArticles(it->first);

    html.append("<div class=\"page\">");
    html.append(QString("<h1>Verkäufernummer %1</h1>").arg(it->first));

    html.append("<h2>Liste der nicht verkauften Artikel</h2>");
    html.append("<table>");

    for (auto itA = unsoldArticles.begin(); itA != unsoldArticles.end(); ++itA)
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
