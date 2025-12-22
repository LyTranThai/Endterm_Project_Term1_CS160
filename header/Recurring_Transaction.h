#pragma once
#include "transaction.h"
#include "Wallet.h"
struct Wallet;
struct Recurring_Transaction_Expense
{
    int id; 
    Date start;
    Date end;
    long long amount;
    Wallet* wallet;
    ExpenseCategory* type;
    string description;
    Recurring_Transaction_Expense()
    {
        Date dum;
        GetCurrentDate(dum);
        amount=0;
        wallet=NULL;
        type=NULL;
        
        description="";
    }

};
struct Recurring_Transaction_Income
{
    int id;
    Date start;
    Date end;
    long long amount;
    Wallet* wallet;
    IncomeSource* type;
    string description;
    Recurring_Transaction_Income()
    {
        Date dum;
        GetCurrentDate(dum);
        amount=0;
        wallet=NULL;
        type=NULL;
        description="";
    }

};

