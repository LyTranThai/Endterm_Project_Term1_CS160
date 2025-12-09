#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Amount.h"
#include "Date.h"
#include "Wallet.h"
#include "Recurring_Transaction.h"
#include "MasterData.h"

struct Transaction_Expense
{

    Date date;
    ExpenseCategory type;
    long long amount;
    Wallet wallet;
    string description;
};

struct Transaction_Income
{

    Date date;
    IncomeSource type;
    long long amount;
    Wallet wallet;
    string description;
};