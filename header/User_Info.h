#pragma once
#include "Transaction.h"
#include "Wallet.h"
#include "Recurring_Transaction.h"
#include "MasterData.h"
#include "InfoArray.h"
struct Wallet_Node;
struct Transaction_Node;

struct User_Info
{
    string name;
    Wallet *default_Wallet;

    Wallet **Wallet_List;
    ExpenseCategory **expense;
    IncomeSource **income;

    Transaction_Income **incomes_transaction;
    int inCount;
    int inCap;

    Transaction_Expense **expenses_transaction;
    int expCount;
    int expCap;
    // Xu ly nhe
    Recurring_Transaction_Expense **Recurring_Transaction_Expense_List;
    Recurring_Transaction_Income **Recurring_Transaction_Income_List;

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

    void SaveToBinary(ofstream &out);
    void LoadFromBinary(ifstream &out);

    void resize();
    // Sort by Date
    void sort_Transaction_List_Date();
    // Check name is not "unknown"
    void check_user_name(string name);

    // Create wallet, update count, resize
    bool create_wallet(string name, int id);

    // find wallet by ID
    bool find_Wallet_ID(int id);
    // find wallet by name
    bool find_Wallet_Name(string name);

    // Create -> sort -> add to Wallet -> sort
    bool create_transaction_expense(Transaction_Expense);
    bool create_transaction_income(Transaction_Income);

    User_Info()
    {
        wallet_capacity = 10; // Start small
        wallet_count = 1;
        Wallet_List = new Wallet *[wallet_capacity];
        Wallet_List[0] = new Wallet;

        Wallet_List[0]->name = "Default";
        default_Wallet = Wallet_List[0];

        expense_count = 1;
        expense_capacity = 10;
        expense = new ExpenseCategory *[expense_capacity];
        expense[0] = new ExpenseCategory;
        expense[0]->name = "Unknown";
        expense[0]->id = 0;
        income_count = 1;
        income_capacity = 10;
        income = new IncomeSource *[income_capacity];
        income[0] = new IncomeSource;
        income[0]->name = "Unknown";
        income[0]->id = 0;
        recur_trans_expense_count = 0;
        recur_trans_expense_capacity = 10;
        Recurring_Transaction_Expense_List = new Recurring_Transaction_Expense *[recur_trans_expense_capacity];
        recur_trans_income_count = 0;
        recur_trans_income_capacity = 10;
        Recurring_Transaction_Income_List = new Recurring_Transaction_Income *[recur_trans_income_capacity];

        inCount = 0;
        inCap = 10;
        incomes_transaction = new Transaction_Income *[inCap];

        expCount = 0;
        expCap = 10;
        expenses_transaction = new Transaction_Expense *[expCap];
    }
    ~User_Info()
    {
        for (int i = 0; i < wallet_count; i++)
        {
            delete Wallet_List[i];
        }
        for (int i = 0; i < expense_count; i++)
        {
            delete expense[i];
        }
        for (int i = 0; i < income_count; i++)
        {
            delete income[i];
        }
        for (int i = 0; i < recur_trans_expense_count; i++)
        {
            delete Recurring_Transaction_Expense_List[i];
        }
        for (int i = 0; i < recur_trans_income_count; i++)
        {
            delete Recurring_Transaction_Income_List[i];
        }
        for (int i = 0; i < expCount; i++)
        {
            delete expenses_transaction[i];
        }
        for (int i = 0; i < inCount; i++)
        {
            delete incomes_transaction[i];
        }

        delete[] Wallet_List;
        delete[] expense;
        delete[] income;
        delete[] Recurring_Transaction_Expense_List;
        delete[] Recurring_Transaction_Income_List;
        delete[] expenses_transaction;
        delete[] incomes_transaction;
    }

    void Show_Wallet_List();
    void Show_Transaction_History();
    void Show_Recurring_Transaction_List();
    void Add_Wallet();
    void Add_Expense();
    void Add_Income();
    void Add_Expense_Transaction();
    void Add_Income_Transaction();
    void Add_Recur_Expense_Transaction();
    void Add_Recur_Income_Transaction();
    bool check_recur_trans(Recurring_Transaction_Expense *&p, Date current_date);
    bool check_recur_trans(Recurring_Transaction_Income *&p, Date current_date);

    // If can not find, return NULL
    Wallet *Choose_Wallet(string name);
    IncomeSource *Choose_IS(string name);
    ExpenseCategory *Choose_EC(string name);
    void Erase_Wallet();
    bool Input_Choice(int &choice);
    void Input_User_Info_Textfile(string filename);

    // Xu ly thong ke:
    //-> Basic Features của 4.Statistics and Reporting

    // Menu
    void Draw_Statistics_Menu();

    void Stats_TimeRange();

    void Stats_Wallet_TimeRange();

    void Stats_Annual_Overview();

    void Stats_Annual_Breakdown();

    bool IsDateInRange(Date target, Date start, Date end);

    //

    //
    //
    //
    //
    bool Is_Wallet_In_Use(int id);
    bool Is_Category_In_Use(int id);
    bool Is_Source_In_Use(int id);
    // mục số 6
    void Edit_Wallet();
    void Delete_Wallet();

    void Edit_ExpenseCategory();
    void Delete_ExpenseCategory();

    void Edit_IncomeSource();
    void Delete_IncomeSource();
    // navigation
    void Draw_MasterData_Menu();
    //
    //
    //
    //
};
