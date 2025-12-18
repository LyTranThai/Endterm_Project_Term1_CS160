#include "Transaction.h"
#include "Wallet.h"
#include "Recurring_Transaction.h"
#include "MasterData.h"
struct Wallet_Node;
struct Transaction_Node;


struct User_Info
{
    string name;
    Wallet* default_Wallet;
    

    Wallet** Wallet_List;
    ExpenseCategory** expense;
    IncomeSource** income;

    Transaction_Income **incomes_transaction;
    int inCount;
    int inCap;

    Transaction_Expense **expenses_transaction;
    int expCount;
    int expCap;
    //Xu ly nhe
    Recurring_Transaction_Expense** Recurring_Transaction_Expense_List;
    Recurring_Transaction_Income** Recurring_Transaction_Income_List;

    int wallet_count;
    int wallet_capacity;
    int expense_count;
    int expense_capacity;
    int income_count;
    int income_capacity;
    int recur_trans_expense_count;
    int recur_trans_expense_capacity;
    int recur_trans_income_count;
    int recur_trans_income_capacity;


    void SaveToBinary(ofstream& out,string filename);
    void LoadFromBinary(ifstream& out,string filename);

    void resize();
    //Sort by Date
    void sort_Transaction_List_Date();
    //Check name is not "unknown"
    void check_user_name(string name);

    //Create wallet, update count, resize
    bool create_wallet(string name, int id);

    //find wallet by ID
    bool find_Wallet_ID(int id);
    //find wallet by name
    bool find_Wallet_Name(string name);

    //Create -> sort -> add to Wallet -> sort
    bool create_transaction_expense(Transaction_Expense);
    bool create_transaction_income(Transaction_Income);

    


    User_Info()
    {
        wallet_capacity = 10; // Start small
        wallet_count = 1;
        Wallet_List = new Wallet*[wallet_capacity];

        Wallet_List[0]->name="Default";
        default_Wallet=Wallet_List[0];

        expense_count=0;
        expense_capacity=10;
        expense=new ExpenseCategory*[expense_capacity];
        income_count=0;
        income_capacity=10;
        income=new IncomeSource*[income_capacity];
        recur_trans_expense_count=0;
        recur_trans_expense_capacity=10;
        Recurring_Transaction_Expense_List= new Recurring_Transaction_Expense*[recur_trans_expense_capacity];
        recur_trans_income_count=0;
        recur_trans_income_capacity=10;
        Recurring_Transaction_Income_List= new Recurring_Transaction_Income*[recur_trans_income_capacity];

        
        inCount=0;
        inCap=10;
        incomes_transaction = new Transaction_Income*[inCap];

        expCount=0;
        expCap=10;
        expenses_transaction=new Transaction_Expense*[expCap];



    }
    ~User_Info()
    {
        delete[] Wallet_List;
        delete[] expense;
        delete[] income;
        delete[] Recurring_Transaction_Expense_List;
        delete[] Recurring_Transaction_Income_List;
    }



};
