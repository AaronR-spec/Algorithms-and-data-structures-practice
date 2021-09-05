#pragma once

#include <iostream>
#include <string>
#include <list>
#include "Product.h"
using namespace std;

// Comparitors

inline bool sortAscRegion(Product& p1, Product& p2)
{

    if (p1.getRegion() != p2.getRegion())
        return p1.getRegion() < p2.getRegion();
    return false;
}
inline bool sortAscCountry(Product& p1, Product& p2)
{

    if (p1.getCountry() != p2.getCountry())
        return p1.getCountry() < p2.getCountry();
    return false;
}
inline bool sortDescRegion(Product& p1, Product& p2)
{

    if (p1.getRegion() != p2.getRegion())
        return p1.getRegion() > p2.getRegion();
    return false;
}
inline bool sortDescCountry(Product& p1, Product& p2)
{

    if (p1.getCountry() != p2.getCountry())
        return p1.getCountry() > p2.getCountry();
    return  false;
}
inline bool sortAescPrice(Product& p1, Product& p2)
{
    float p1Price = p1.getUnitPrice() * p1.getQuantity();
    float p2Price = p2.getUnitPrice() * p2.getQuantity();

    if (p1Price != p2Price)
        return p1Price < p2Price;
    return  false;
}
