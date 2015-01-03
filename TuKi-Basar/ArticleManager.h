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

private:
    QList<Article*> articles;
};

#endif // ARTICLEMANAGER_H
