#pragma once
#include "MasterData.h"
#include "Recurring_Transaction.h"
#include "Wallet.h"

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




bool isLeapYear(int year);

// helper
int getDaysInMonth(int month, int year);

// nhập sai ngày là bt đấy :)), I'm watching you
bool isValidDate(const Date &d);

// chuyển date string
string dateToString(const Date &d);

// chuyển string date
bool stringToDate(const string &str, Date &outDate);

bool isValidDouble(const string &s);

// check int
bool isValidInt(const string &s);

bool isValidLongLong(const string &s);