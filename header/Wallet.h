#pragma once
#include "MasterData.h"
#include "DataHandling.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
// xóa bớt include r :)), include lắm thành vòng lặp
struct Transaction_Income;
struct Transaction_Expense;

struct Amount;

struct Wallet : MasterData
{
    // id đồ lấy bên master luôn
    long long remain;

    Transaction_Income **incomes;
    int inCount;
    int inCap;

    Transaction_Expense **expenses;
    int expCount;
    int expCap;

    Wallet()
    {
        name="unknown";
        id=0;
        remain=0;
        inCount = 0;
        inCap = 10;
        expCount = 0;
        expCap = 10;
        incomes = new Transaction_Income*[inCap];
        expenses = new Transaction_Expense*[expCap];
    }

    Wallet& operator=(const Wallet &src);
    bool Input_Wallet(string info);
    void Output_Terminal();

    // Thêm 2 func input output binary file đây nha:
    void SaveToBinary(string filename);
    void LoadFromBinary(string filename);
    void Wallet_resize();
    
};

Wallet& Wallet::operator=(const Wallet &src)
{

    if (this == &src)
        return *this;


    this->id = src.id;
    this->name = src.name;
    this->remain = src.remain;
    this->inCount = src.inCount;
    this->inCap = src.inCap;
    this->expCount=src.expCount;
    this->expCap=src.expCap;
    this->incomes = new Transaction_Income*[src.inCap];
    this->expenses = new Transaction_Expense*[src.expCap];
    for(int i = 0; i < src.inCount; i++) 
    {
        this->incomes[i]=src.incomes[i];
    }
    for(int i=0; i< src.expCount; i++)
    {
        this->expenses[i]=src.expenses[i];
    }
    return *this;
}

// Format
// ID-Name-remain

template <typename T>
void resize(T*& array, int& size,int& capcity);
template <typename T>
void add_element(T*& array, int& size,int& capcity, T element);



