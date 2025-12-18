#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Amount.h"
#include "Date.h"
#include "Wallet.h"
#include "Recurring_Transaction.h"
#include "InfoArray.h"
<<<<<<< Updated upstream
=======

struct Date;
struct Transaction_Type;
struct Amount;
struct Wallet;


>>>>>>> Stashed changes

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
    //Format
    // Date/Month/Year^Type of transaction ^Amount^WalletName^Description
    bool Transaction_Income::Input_Transaction(string info,IncomeSourceArray array);
    bool Output_Terminal(Transaction_Income);
};

