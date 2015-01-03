#ifndef ARTICLE_H
#define ARTICLE_H

#include <QString>

class Article
{
public:
    Article(unsigned int articleNumber, unsigned int sellerNumber, double prize, QString description);

private:
    bool m_sold;
    unsigned int m_articleNumber;
    unsigned int m_sellerNumber;
    double m_prize;
    QString m_description;
};

#endif // ARTICLE_H
