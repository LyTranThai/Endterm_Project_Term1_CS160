#pragma once
#include <iostream>
using namespace std;
#include "Amount.h"
#include "Date.h"
#include "Transaction_Type.h"
#include "Wallet.h"

struct Date;
struct Transaction_Type;
struct Amount;
struct Wallet;



struct Transaction
{

    Date date;
    Transaction_Type type;
    long long amount;
    Wallet wallet;
    string description;
};

