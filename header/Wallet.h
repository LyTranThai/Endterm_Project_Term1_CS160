#pragma once
#include <iostream>
using namespace std;
#include "Amount.h"

struct Amount;


struct Wallet
{
    int ID;
    string name;
    Amount remain;
};