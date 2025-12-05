#include "Transaction.h"
#include "Wallet.h"
#include "Recurring_Transaction.h"
struct Wallet_Node;
struct Transaction_Node;


struct User_Info
{
    string name;
    Wallet default_Wallet;
    Wallet* Wallet_List;
    Transaction* Transaction_History;
    Recurring_Transaction* Recurring_Transaction_List;
    int wallet_count;
    int wallet_capacity;
    int trans_count;
    int trans_capacity;
    User_Info()
    {
        wallet_capacity = 10; // Start small
        wallet_count = 0;
        Wallet_List = new Wallet[wallet_capacity];

        trans_capacity = 10;
        trans_count = 0;
        Recurring_Transaction_List = new Recurring_Transaction[trans_capacity];
    }
    ~User_Info()
    {
        delete[] Wallet_List;
        delete[] Transaction_History;
        delete[]Recurring_Transaction_List;
    }

    //Sort by Date
    void sort_Transaction_List_Date();
};
