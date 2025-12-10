#pragma once
#include "MasterData.h"
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
<<<<<<< Updated upstream
    // id đồ lấy bên master luôn
=======
    string ID;
>>>>>>> Stashed changes
    string name;
    long long remain;

    Transaction_Income *incomes;
    int inCount;
    int inCap;

    Transaction_Expense *expenses;
    int expCount;
    int expCap;

    bool Input_Wallet(string info);
    void Output_Terminal();
<<<<<<< Updated upstream

    // Thêm 2 func input output binary file đây nha:
    void SaveToBinary(string filename);
    void LoadFromBinary(string filename);
};

// Format
// ID-Name-remain
=======
    bool Input_Wallet();
};

template <typename T>
void resize(T*& array, int& size,int& capcity);
template <typename T>
void add_element(T*& array, int& size,int& capcity, T element);



>>>>>>> Stashed changes
