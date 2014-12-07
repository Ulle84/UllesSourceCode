#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

class ProductItem
{
public:
    ProductItem();

private:
    unsigned int m_articleNumber;
    unsigned int m_sellerNumber;
    double m_prize;
    QString m_description;
};

#endif // PRODUCTITEM_H
