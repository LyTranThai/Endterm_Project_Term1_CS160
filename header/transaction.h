#pragma once
#include <iostream>
using namespace std;
#include "Amount.h"
#include "Date.h"
#include "Transaction_Type.h"
#include "Wallet.h"
#include "Recurring_Transaction.h"
#include "MasterData.h"

struct Date;
struct Transaction_Type;
struct Amount;
struct Wallet;



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