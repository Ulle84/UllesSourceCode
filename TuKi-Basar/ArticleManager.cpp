#include "ArticleManager.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QVariant>

ArticleManager::ArticleManager()
{
    m_fileName = "Articles.xml";
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
            unsigned int articleNumber;
            unsigned int sellerNumber;
            double prize;
            QString size;
            QString description;

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
                else
                {
                    xml.skipCurrentElement();
                }
            }

            Article* article = new Article(articleNumber, sellerNumber, prize, size, description);
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

QString ArticleManager::currentSaleToText()
{
    QString currentSaleText = "Ver  Art  Preis   Beschreibung\n";
    for (auto it = m_currentSale.begin(); it != m_currentSale.end(); ++it)
    {
        currentSaleText += QString("%1  %2  %3  %4\n").arg((*it)->m_sellerNumber).arg((*it)->m_articleNumber).arg(prizeToString((*it)->m_prize)).arg((*it)->m_description);
    }
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
