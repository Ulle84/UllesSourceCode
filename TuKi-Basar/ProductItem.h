#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QString>

class ProductItem
{
public:
    ProductItem(QString input);
    ProductItem(unsigned int articleNumber, unsigned int sellerNumber, double prize, QString description);

private:
    bool sold;
    unsigned int m_articleNumber;
    unsigned int m_sellerNumber;
    double m_prize;
    QString m_description;
};

#endif // PRODUCTITEM_H
