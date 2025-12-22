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



struct Transaction_Expense
{
    int id=0;
    Date date;
    ExpenseCategory* type;
    long long amount;
    Wallet* wallet;
    string description;

    void SaveToBinary(ofstream& out,string filename);
    void LoadFromBinary(ifstream& out,string filename);
};

struct Transaction_Income
{
    int id=0;
    Date date;
    IncomeSource* type;
    long long amount;
    Wallet* wallet;
    string description;
    //Format
    // Date/Month/Year^Type of transaction ^Amount^WalletName^Description
    //bool Input_Transaction(string info,IncomeSourceArray array);
    bool Output_Terminal(Transaction_Income);

    void SaveToBinary(string filename);
    void LoadFromBinary(string filename);
};

