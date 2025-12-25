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
        name = "unknown";
        id = 0;
        remain = 0;
        inCount = 0;
        inCap = 10;
        expCount = 0;
        expCap = 10;
        incomes = new Transaction_Income *[inCap];
        expenses = new Transaction_Expense *[expCap];
        for(int i=0; i<inCap; i++)
        {
            incomes[i]=NULL;
        }
        for(int i=0; i<expCap; i++)
        {
            expenses[i]=NULL;
        }
    }


    ~Wallet()
    {
        delete[] incomes;
        delete[] expenses;
    }

    Wallet &operator=(const Wallet &src);
    bool Input_Wallet(string info);
    void Output_Terminal();

    // Thêm 2 func input output binary file đây nha:
    void SaveToBinary(string filename);
    void LoadFromBinary(string filename);
    void Wallet_resize();
    void Wallet_resize_no_copy();
};

// Format
// ID-Name-remain

template <typename T>
void resize(T *&array, int &size, int &capcity);
template <typename T>
void add_element(T *&array, int &size, int &capcity, T element);
