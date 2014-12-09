#include "ProductItemManager.h"

ProductItemManager::ProductItemManager()
{
}

ProductItemManager::~ProductItemManager()
{
    for (auto it = productItems.begin(); it != productItems.end(); ++it)
    {
        delete *it;
    }
}

void ProductItemManager::addProductItem(ProductItem* productItem)
{
    productItems.append(productItem);
}
