#pragma once
#include "transaction.h"
struct Recurring_Transaction_Expense
{
    ExpenseCategory type;
    long long amount;
    Wallet wallet;
    string description;
    Date start;
    Date end;
};
struct Recurring_Transaction_Income
{
    IncomeSource type;
    long long amount;
    Wallet wallet;
    string description;
    Date start;
    Date end;
};
