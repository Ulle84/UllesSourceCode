#include "Article.h"

Article::Article(unsigned int articleNumber, unsigned int sellerNumber, unsigned int soldOnPc, double prize, QString size, QString description, QString soldTime)
  : m_articleNumber(articleNumber),
    m_sellerNumber(sellerNumber),
    m_prize(prize),
    m_description(description),
    m_size(size),
    m_soldOnPc(soldOnPc),
    m_soldTime(soldTime)
{

}
