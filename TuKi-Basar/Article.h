#ifndef ARTICLE_H
#define ARTICLE_H

#include <QString>

class Article
{
//friend class ArticleManager;

public:
    Article(unsigned int articleNumber, unsigned int sellerNumber, double prize, QString size, QString description);

    bool m_sold;
    unsigned int m_articleNumber;
    unsigned int m_sellerNumber;
    double m_prize;
    QString m_size;
    QString m_description;

private:
    //TODO declare variables private again?
};

#endif // ARTICLE_H
