#include "ArticleManager.h"

ArticleManager::ArticleManager()
{
}

ArticleManager::~ArticleManager()
{
    for (auto it = articles.begin(); it != articles.end(); ++it)
    {
        delete *it;
    }
}

void ArticleManager::addArticle(Article* article)
{
    articles.append(article);
}
