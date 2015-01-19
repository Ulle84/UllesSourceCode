#include "ArticleManager.h"

#include <map>

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QVariant>
#include <QDateTime>
#include <QStringList>

#include "Settings.h"
#include "Statistics.h"

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

void ArticleManager::setFileName(QString fileName)
{
  m_fileName = fileName;
}

QString ArticleManager::getFileName()
{
  return m_fileName;
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

bool ArticleManager::isArticleInCurrentSale(unsigned int sellerNumber, unsigned int articleNumber)
{
  for (auto it = m_currentSale.begin(); it != m_currentSale.end(); ++it)
  {
    if ((*it)->m_sellerNumber == sellerNumber && (*it)->m_articleNumber == articleNumber)
    {
      return true;
    }
  }
  return false;
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

void ArticleManager::calculateStatistics(Statistics* statistics)
{
  statistics->m_volumeOfSale = 0.0;
  statistics->m_countOfSoldArticles = 0;

  statistics->m_deductionPercentage = m_settings->getDeductionPercentage();


  QStringList transactions;

  for (auto it = m_articles.begin(); it != m_articles.end(); it++)
  {
    //if ((*it)->m_soldOnPc == m_settings->getPc())
    if ((*it)->m_soldOnPc != 0)
    {
      QString transaction = QString("%1 %2").arg((*it)->m_soldOnPc).arg((*it)->m_soldTime);

      statistics->m_volumeOfSale += (*it)->m_prize;
      (statistics->m_countOfSoldArticles)++;
      if (!transactions.contains(transaction))
      {
        transactions.append(transaction);
      }
    }
  }

  statistics->m_countOfSales = transactions.length();
  if (statistics->m_countOfSales == 0)
  {
    statistics->m_articlesPerSale = 0;
  }
  else
  {
    statistics->m_articlesPerSale = statistics->m_countOfSoldArticles * 1.0 / statistics->m_countOfSales;
  }
  statistics->m_deduction = statistics->m_volumeOfSale * m_settings->getDeductionPercentage() / 100.0;

  statistics->m_countOfAllArticles = m_articles.length();

  if (statistics->m_countOfAllArticles == 0)
  {
    statistics->m_percentageOfSoldArticles = 0.0;
  }
  else
  {
    statistics->m_percentageOfSoldArticles = statistics->m_countOfSoldArticles * 100.0 / statistics->m_countOfAllArticles;
  }
}

std::map<int, double> ArticleManager::getSalesPerSeller()
{
  std::map<int, double> map;

  for (int i = m_settings->getSellerMin(); i <= m_settings->getSellerMax(); i++)
  {
    map[i] = 0.0;
  }

  for (auto it = m_articles.begin(); it != m_articles.end(); ++it)
  {
    if ((*it)->m_soldOnPc == 0)
    {
      continue;
    }

    if (map.find((*it)->m_sellerNumber) == map.end())
    {
      // this should not happen, since we check the seller number at input
      map[(*it)->m_sellerNumber] = 0.0;
    }

    map[(*it)->m_sellerNumber] += (*it)->m_prize;
  }

  return map;
}

std::map<int, double> ArticleManager::getSoldArticles(int sellerNumber)
{
  std::map<int, double> map;

  for (auto it = m_articles.begin(); it != m_articles.end(); ++it)
  {
    if ((*it)->m_soldOnPc == 0)
    {
      continue;
    }

    if ((*it)->m_sellerNumber != sellerNumber)
    {
      continue;
    }

    map[(*it)->m_articleNumber] = (*it)->m_prize;
  }

  return map;
}

std::map<int, double> ArticleManager::getUnsoldArticles(int sellerNumber)
{
  std::map<int, double> map;

  for (auto it = m_articles.begin(); it != m_articles.end(); ++it)
  {
    if ((*it)->m_soldOnPc != 0)
    {
      continue;
    }

    if ((*it)->m_sellerNumber != sellerNumber)
    {
      continue;
    }

    map[(*it)->m_articleNumber] = (*it)->m_prize;
  }

  return map;
}

std::map<int, int> ArticleManager::getSoldArticlesPerSeller()
{
  std::map<int, int> map;

  for (int i = m_settings->getSellerMin(); i <= m_settings->getSellerMax(); i++)
  {
    map[i] = 0;
  }

  for (auto it = m_articles.begin(); it != m_articles.end(); ++it)
  {
    if ((*it)->m_soldOnPc == 0)
    {
      continue;
    }

    if (map.find((*it)->m_sellerNumber) == map.end())
    {
      // this should not happen, since we check the seller number at input
      map[(*it)->m_sellerNumber] = 0;
    }

    map[(*it)->m_sellerNumber]++;
  }

  return map;
}

std::map<int, int> ArticleManager::getOfferedArticlesPerSeller()
{
  std::map<int, int> map;

  for (int i = m_settings->getSellerMin(); i <= m_settings->getSellerMax(); i++)
  {
    map[i] = 0;
  }

  for (auto it = m_articles.begin(); it != m_articles.end(); ++it)
  {
    if (map.find((*it)->m_sellerNumber) == map.end())
    {
      // this should not happen, since we check the seller number at input
      map[(*it)->m_sellerNumber] = 0;
    }

    map[(*it)->m_sellerNumber]++;
  }

  return map;
}

std::map<QString, int> ArticleManager::getSoldArticlesInRanges()
{
  //TODO think about performance

  std::map<QString, int> output;

  int maxCountOfArticles = m_settings->getArticleMax() - m_settings->getArticleMin() + 1;

  for (int i = 0; i <= maxCountOfArticles; i += 10)
  {
    output[QString("%1 - %2").arg(i).arg(i+9)] = 0;
  }

  std::map<int, int> soldArticlesPerSeller = getSoldArticlesPerSeller();

  for (auto it = soldArticlesPerSeller.begin(); it != soldArticlesPerSeller.end(); ++it)
  {
    int value = it->second / 10;
    output[QString("%1 - %2").arg(value).arg(value+9)]++;
  }

  return output;
}

std::map<QString, int> ArticleManager::getOfferedArticlesInRanges()
{
  //TODO think about performance

  std::map<QString, int> output;

  int maxCountOfArticles = m_settings->getArticleMax() - m_settings->getArticleMin() + 1;

  for (int i = 0; i <= maxCountOfArticles; i += 10)
  {
    output[QString("%1 - %2").arg(i).arg(i+9)] = 0;
  }

  std::map<int, int> offeredArticlesPerSeller = getOfferedArticlesPerSeller();

  for (auto it = offeredArticlesPerSeller.begin(); it != offeredArticlesPerSeller.end(); ++it)
  {
    int value = it->second / 10;
    output[QString("%1 - %2").arg(value).arg(value+9)]++;
  }

  return output;
}

void ArticleManager::sync(ArticleManager *other)
{
  for (auto it = other->m_articles.begin(); it != other->m_articles.end(); it++)
  {
    if ((*it)->m_soldOnPc != 0)
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
          // TODO article was also sold on this PC, what shall we do? which prize shall we take?
        }
      }
      else
      {
        Article* newArticle = new Article((*it)->m_articleNumber, (*it)->m_sellerNumber, (*it)->m_soldOnPc, (*it)->m_prize, (*it)->m_size, (*it)->m_description, (*it)->m_soldTime);
        m_articles.append(newArticle);
      }
    }
  }
}

double ArticleManager::getPayOutFactor()
{
  return (100.0 - m_settings->getDeductionPercentage()) / 100.0;
}
