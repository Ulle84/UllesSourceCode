#include "Article.h"

Article::Article(unsigned int articleNumber, unsigned int sellerNumber, double prize, QString size, QString description)
    : m_articleNumber(articleNumber),
      m_sellerNumber(sellerNumber),
      m_prize(prize),
      m_description(description),
      m_size(size),
      m_sold(false)
{

}
