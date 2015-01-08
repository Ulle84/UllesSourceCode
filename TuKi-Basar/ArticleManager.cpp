#include "ArticleManager.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QVariant>
#include <QDateTime>
#include <QStringList>

#include "Settings.h"

ArticleManager::ArticleManager(Settings* settings, QString fileName)
  : m_settings(settings),
    m_fileName(fileName)
{
  fromXml();
}

ArticleManager::~ArticleManager()
{
  for (auto it = m_articles.begin(); it != m_articles.end(); ++it)
  {
    delete *it;
  }
}

void ArticleManager::addArticle(Article* article)
{
  m_articles.append(article);
}

void ArticleManager::clear()
{
  m_articles.clear();
}

Article* ArticleManager::getArticle(int sellerNumber, int articleNumber)
{
  for (auto it = m_articles.begin(); it != m_articles.end(); it++)
  {
    if ((*it)->m_sellerNumber == sellerNumber && (*it)->m_articleNumber == articleNumber)
    {
      return *it;
    }
  }
  return 0;
}

bool ArticleManager::fromXml()
{
  QFile file(m_fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    return false;
  }

  QXmlStreamReader xml(&file);

  if (!xml.readNextStartElement())
  {
    return false;
  }

  if (xml.name() != "TuKiBazarArticles")
  {
    return false;
  }

  while (xml.readNextStartElement())
  {
    if (xml.name() == "Article")
    {
      unsigned int articleNumber = 0;
      unsigned int sellerNumber = 0;
      unsigned int soldOnPc = 0;
      double prize = 0.0;
      QString size;
      QString description;
      QString soldTime;

      while (xml.readNextStartElement())
      {
        if (xml.name() == "Seller")
        {
          sellerNumber = xml.readElementText().toInt();
        }
        else if (xml.name() == "Number")
        {
          articleNumber = xml.readElementText().toInt();
        }
        else if (xml.name() == "Prize")
        {
          prize = xml.readElementText().toDouble();
        }
        else if (xml.name() == "Size")
        {
          size = xml.readElementText();
        }
        else if (xml.name() == "Description")
        {
          description = xml.readElementText();
        }
        else if (xml.name() == "SoldOnPc")
        {
          soldOnPc = xml.readElementText().toInt();
        }
        else if (xml.name() == "SoldTime")
        {
          soldTime = xml.readElementText();
        }
        else
        {
          xml.skipCurrentElement();
        }
      }

      Article* article = new Article(articleNumber, sellerNumber, soldOnPc, prize, size, description, soldTime);
      addArticle(article);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }

  return true;
}

bool ArticleManager::toXml()
{
  QFile file(m_fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    return false;
  }

  QXmlStreamWriter xml(&file);
  xml.setAutoFormatting(true);
  xml.setAutoFormattingIndent(2);
  xml.writeStartDocument();

  xml.writeStartElement("TuKiBazarArticles");

  for (auto it = m_articles.begin(); it != m_articles.end(); ++it)
  {
    xml.writeStartElement("Article");
    xml.writeTextElement("Seller", QString("%1").arg((*it)->m_sellerNumber));
    xml.writeTextElement("Number", QString("%1").arg((*it)->m_articleNumber));
    xml.writeTextElement("Prize", QString("%1").arg((*it)->m_prize));
    xml.writeTextElement("Size", (*it)->m_size);
    xml.writeTextElement("Description", (*it)->m_description);
    xml.writeTextElement("SoldOnPc", QString("%1").arg((*it)->m_soldOnPc));
    xml.writeTextElement("SoldTime", (*it)->m_soldTime);
    xml.writeEndElement(); // Article
  }

  xml.writeEndElement(); // TuKiBazarArticles
  xml.writeEndDocument();

  file.close();

  return true;
}

void ArticleManager::resetCurrentSale()
{
  m_currentSale.clear();
}

void ArticleManager::addArticleToCurrentSale(Article* article)
{
  m_currentSale.append(article);
}

void ArticleManager::removeLastArticleFromCurrentSale()
{
  if (m_currentSale.length() > 0)
  {
    m_currentSale.removeLast();
  }
}

void ArticleManager::finishCurrentSale(unsigned int pcNumber)
{
  QString soldTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

  for (auto it = m_currentSale.begin(); it != m_currentSale.end(); ++it)
  {
    (*it)->m_soldOnPc = pcNumber;
    (*it)->m_soldTime = soldTime;
  }

  resetCurrentSale();
  toXml();
}

bool ArticleManager::isCurrentSaleEmpty()
{
  return m_currentSale.isEmpty();
}

Article *ArticleManager::getLastArticleInCurrentSale()
{
  Article* article = 0;
  if (m_currentSale.length() > 0)
  {
    article = m_currentSale.last();
  }
  return article;
}

QString ArticleManager::currentSaleToText()
{
  if (m_currentSale.length() < 1)
  {
    return QString();
  }

  double sum = 0;

  QString currentSaleText = "Ver  Art  Preis   Beschreibung\n";
  for (auto it = m_currentSale.begin(); it != m_currentSale.end(); ++it)
  {
    currentSaleText += QString("%1  %2  %3  %4\n").arg((*it)->m_sellerNumber).arg((*it)->m_articleNumber).arg(prizeToString((*it)->m_prize)).arg((*it)->m_description);
    sum += (*it)->m_prize;
  }
  currentSaleText += "\n";
  currentSaleText += QString("Summe:    %1").arg(prizeToString(sum));
  return currentSaleText;
}

QString ArticleManager::currentSaleToHtml()
{
  QString currentSaleHtml;
  currentSaleHtml += "<!DOCTYPE html>";
  currentSaleHtml += "<meta charset=\"utf-8\">";
  currentSaleHtml += "<html>";
  currentSaleHtml += "<style>\
      table {\
      font-size: 14pt;\
border: 2px solid black;\
  border-spacing: 0px;\
}\
\
th, td {\
  text-align: center;\
  min-width: 30px;\
padding: 5px 5px 5px 5px;\
  vertical-align: middle;\
  border-bottom: 1px solid grey;\
  border-right: 1px solid grey;\
}\
\
td:last-child, th:last-child {\
  border-right: 0px;\
}\
\
tr:last-child > td {\
  border-bottom: 0px;\
}";
currentSaleHtml += "</style>";
currentSaleHtml += "<table>";
currentSaleHtml += "<tr>";
currentSaleHtml += "<th>Verkäufernummer</th>";
currentSaleHtml += "<th>Artikelnummer</th>";
currentSaleHtml += "<th>Preis</th>";
currentSaleHtml += "<th>Beschreibung</th>";
currentSaleHtml += "</tr>";

for (auto it = m_currentSale.begin(); it != m_currentSale.end(); ++it)
{
  currentSaleHtml += "<tr>";
  currentSaleHtml += QString("<td>%1</td>").arg((*it)->m_sellerNumber);
  currentSaleHtml += QString("<td>%1</td>").arg((*it)->m_articleNumber);
  currentSaleHtml += QString("<td>%1 &euro;</td>").arg((*it)->m_prize);
  currentSaleHtml += QString("<td>%1</td>").arg((*it)->m_description);
  currentSaleHtml += "</tr>";
}

currentSaleHtml += "</table>";
currentSaleHtml += "</html>";

return currentSaleHtml;
}

QString ArticleManager::prizeToString(double prize)
{
  QString string = QString::number(prize, 'f', 2).replace('.', ',');

  if (prize < 100)
  {
    string.prepend(" ");
  }

  if (prize < 10)
  {
    string.prepend(" ");
  }

  return string;
}

void ArticleManager::calculateStatistics(double* volumeOfSale, double* deduction, double* deductionPercentage, int* countOfSales, int* countOfSoldArticles, double* articlesPerSale)
{
  *volumeOfSale = 0.0;
  *countOfSoldArticles = 0;

  *deductionPercentage = m_settings->getDeductionPercentage();


  QStringList transactions;

  for (auto it = m_articles.begin(); it != m_articles.end(); it++)
  {
    //if ((*it)->m_soldOnPc == m_settings->getPc())
    if ((*it)->m_soldOnPc != 0)
    {
      QString transaction = QString("%1 %2").arg((*it)->m_soldOnPc).arg((*it)->m_soldTime);

      *volumeOfSale += (*it)->m_prize;
      (*countOfSoldArticles)++;
      if (!transactions.contains(transaction))
      {
        transactions.append(transaction);
      }
    }
  }

  *countOfSales = transactions.length();
  if (*countOfSales == 0)
  {
    *articlesPerSale = 0;
  }
  else
  {
    *articlesPerSale = *countOfSoldArticles * 1.0 / *countOfSales;
  }
  *deduction = *volumeOfSale * m_settings->getDeductionPercentage() / 100.0;
}

void ArticleManager::sync(ArticleManager *other)
{
  // check if article was sold on other PC -> show error
  for (auto it = other->m_articles.begin(); it != other->m_articles.end(); it++)
  {
    if ((*it)->m_soldOnPc != 0) //TODO do more checks
    {
      Article* article = getArticle((*it)->m_sellerNumber, (*it)->m_articleNumber);
      if (article != 0)
      {
        if (article->m_soldOnPc == 0)
        {
          article->m_soldOnPc = (*it)->m_soldOnPc;
          article->m_soldTime = (*it)->m_soldTime;
        }
        else
        {
          // what is to do?
        }
      }
      else
      {
        // append new article or error?
      }
    }
  }
}
