#pragma once
#include <iostream>
#include "Currency.h"
using namespace std;





struct Amount
{
    double quantity;
    Currency currency;
    Amount()
    {
        currency.unit="VND";
    }
};

//format
//quantity/currency
void Input_Amount(string info);

