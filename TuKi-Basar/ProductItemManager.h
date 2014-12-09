#ifndef PRODUCTITEMMANAGER_H
#define PRODUCTITEMMANAGER_H

#include <QList>

#include "ProductItem.h"

class ProductItemManager
{
public:
    ProductItemManager();
    ~ProductItemManager();

    void addProductItem(ProductItem* productItem);

private:
    QList<ProductItem*> productItems;
};

#endif // PRODUCTITEMMANAGER_H
