#pragma once
#include <iostream>
#include "Currency.h"
using namespace std;





struct Amount
{
    int quantity;
    Currency currency;
    Amount()
    {
        currency.unit="VND";
    }
};


