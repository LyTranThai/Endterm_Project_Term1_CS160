#pragma once
#include "transaction.h"
struct Recurring_Transaction_Expense
{

    Date start;
    Date end;
    long long amount;
    Wallet* wallet;
    ExpenseCategory* type;
    string description;

};
struct Recurring_Transaction_Income
{
    Date start;
    Date end;
    long long amount;
    Wallet* wallet;
    IncomeSource* type;
    string description;

};
