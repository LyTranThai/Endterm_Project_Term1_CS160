#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Amount.h"
#include "Date.h"
#include "Wallet.h"
#include "InfoArray.h"
#include "DataHandling.h"

struct Date;
struct Transaction_Type;
struct Amount;
struct Wallet;

struct transaction
{
    int id=0;
    Date date;
    long long amount;
    Wallet* wallet;
    string description;
};

struct Transaction_Expense:transaction
{
    ExpenseCategory* type;
};

struct Transaction_Income:transaction
{
    IncomeSource* type;
};

