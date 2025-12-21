#pragma once
#include "Date.h"
#include "Wallet.h"
#include "MasterData.h"
struct Recurring_Transaction_Expense
{

    Date start;
    Date end;
    long long amount;
    Wallet *wallet;
    ExpenseCategory *type;
    string description;
    Recurring_Transaction_Expense()
    {
        Date dum;
        GetCurrentDate(dum);
        amount = 0;
        wallet = NULL;
        type = NULL;
        description = "";
    }
};
struct Recurring_Transaction_Income
{
    Date start;
    Date end;
    long long amount;
    Wallet *wallet;
    IncomeSource *type;
    string description;
    Recurring_Transaction_Income()
    {
        Date dum;
        GetCurrentDate(dum);
        amount = 0;
        wallet = NULL;
        type = NULL;
        description = "";
    }
};
