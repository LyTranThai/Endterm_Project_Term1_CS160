#include "Transaction.h"
#include "Wallet.h"
struct Wallet_Node;
struct Transaction_Node;


struct User_Info
{
    string name;
    Wallet default_Wallet;
    Wallet* Wallet_List=new Wallet[100];
    Transaction* Transaction_List=new Transaction[100];
    int number_of_wallets = 0 ;
    int number_of_transaction = 0;
    ~User_Info()
    {
        delete[] Wallet_List;
        delete[] Transaction_List;
    }

    //Sort by Date
    void sort_Transaction_List_Date();
};
