#ifndef ARTICLEMANAGER_H
#define ARTICLEMANAGER_H

#include <QList>

#include "Article.h"

class ArticleManager
{
public:
    ArticleManager();
    ~ArticleManager();

    void addArticle(Article* article);

    bool fromXml();
    bool toXml();

private:
    QList<Article*> m_articles;
    QString m_fileName;
};

#endif // ARTICLEMANAGER_H
