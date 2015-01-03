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
