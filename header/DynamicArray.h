#include "MasterData.h"

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
};

const int INITIAL_CAPACITY = 10;
