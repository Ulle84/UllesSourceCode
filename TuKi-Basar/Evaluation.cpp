﻿#include "Evaluation.h"
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

QString Evaluation::createHtmlCodeOverview()
{
  QString html;
  html.append("<!DOCTYPE html>");
  html.append("<html><head>");
  html.append("<meta charset=\"utf-8\">");
  html.append("<title></title></head><body>");
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

  std::map<QString, int> soldArticlesInRanges = m_articleManager->getSoldArticlesInRanges();

  html.append("<table>");
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
  html.append("<meta charset=\"utf-8\">");
  html.append("<style>");
  html.append("body, h1, html{margin: 0px; padding: 0px;}");
  html.append(".page{min-height: 26.85cm; max-height: 26.85cm; border-bottom: 1px solid black;}"); //TODO remove border
  html.append("</style>");
  html.append("<title></title></head><body>");

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

QString Evaluation::createHtmlCodeUnsoldArticles()
{
  QString html;
  html.append("<!DOCTYPE html>");
  html.append("<html><head>");
  html.append("<meta charset=\"utf-8\">");
  html.append("<style>");
  html.append("body, h1, html{margin: 0px; padding: 0px;}");
  html.append(".page{min-height: 26.85cm; max-height: 26.85cm; border-bottom: 1px solid black;}"); //TODO remove border
  html.append("</style>");
  html.append("<title></title></head><body>");

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
