#pragma once

#include <iostream>
#include <list>
#include "Product.h"
using namespace std;

inline float totalValueOfSales(list<Product>& products)
{
    float valueOfSales = 0;
    float productValue = 0;
    for (auto p : products)
    {
        productValue = (p.getUnitPrice() * p.getQuantity());
        valueOfSales += productValue;
    }
    return valueOfSales;
}
inline int totalQuantityOfSales(list<Product>& products)
{
    int quantityOfSales = 0;
    for (auto p : products)
    {
        quantityOfSales += p.getQuantity();
    }
    return quantityOfSales;
}
inline float averageValueOfSales(list<Product>& products)
{
    float totalValue = totalValueOfSales(products);
    int totalQuantity = totalQuantityOfSales(products);

    return (totalValue / totalQuantity);

}