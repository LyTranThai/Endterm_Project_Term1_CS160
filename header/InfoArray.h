#include "MasterData.h"
#include "Recurring_Transaction.h"
#include "Wallet.h"
#pragma once
struct ExpenseCategoryArray
{
    ExpenseCategory *data;
    int size;
    int capacity;
};

struct IncomeSourceArray
{
    IncomeSource *data;
    int size;
    int capacity;
};

struct WalletArray
{
    Wallet *data;
    int size;
    int capacity;
    WalletArray()
    {
        capacity = 10;
        size = 0;
        data = new Wallet[capacity];
    }

    //Format
    //ID-Name-remain
    bool Input_With_Textfile(string filename);
    bool Output_Save_Textfile(string filename);
};

const int INITIAL_CAPACITY = 10;

struct Recurring_Transaction_Enpense_List
{
    /* data */
};
