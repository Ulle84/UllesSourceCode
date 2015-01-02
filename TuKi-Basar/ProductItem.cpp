#include "ProductItem.h"

ProductItem::ProductItem(unsigned int articleNumber, unsigned int sellerNumber, double prize, QString description)
    : m_articleNumber(articleNumber),
      m_sellerNumber(sellerNumber),
      m_prize(prize),
      m_description(description),
      m_sold(false)
{

}
