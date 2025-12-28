#include "../header/User_Info.h"



void PrintDateTable(Date d)
{
    cout << right << setfill('0') << setw(2) << d.day << "/"
         << setw(2) << d.month << "/"
         << setw(4) << d.year << setfill(' ');
}

const int width = 70;

void User_Info::Show_Wallet_List()
{
    cout << "\n";

    // Header
    cout << left << setw(8) << "ID"
         << left << setw(25) << "Wallet Name"
         << right << setw(20) << "Balance" << endl;
    cout << string(width, '-') << endl;

    if (wallet_count == 0)
    {
        cout << " [!] No wallets found.\n";
    }
    else
    {
        for (int i = 0; i < wallet_count; i++)
        {
            cout << left << setw(8) << Wallet_List[i]->id
                 << left << setw(25) << Wallet_List[i]->name
                 << right << setw(20) << Wallet_List[i]->remain << endl;
        }
    }
    cout << string(width, '=') << endl;
}


void User_Info::Show_Transaction_History()
{
    // Define standard widths
    const int wDate = 14;
    const int wCat = 22;
    const int wWal = 18;
    const int wAmt = 15;

    cout << "\n";

    // 1. INCOME TABLE
    if (inCount > 0)
    {
        cout << "\n [INCOME HISTORY]\n";
        Show_Transaction(this->incomes_transaction, this->inCount);
    }

    // 2. EXPENSE TABLE
    if (expCount > 0)
    {
        cout << "\n [EXPENSE HISTORY]\n";
        Show_Transaction(this->expenses_transaction, this->expCount);
    }

    if (inCount == 0 && expCount == 0)
    {
        cout << " [!] No transaction history found.\n";
    }
    cout << string(width, '-') << endl;
}

void User_Info::Show_All_Transaction_History()
{
    // Define standard widths
    const int wDate = 14;
    const int wCat = 22;
    const int wWal = 18;
    const int wAmt = 15;

    cout << "\n";

    // 1. INCOME TABLE
    if (inCount > 0)
    {
        cout << "\n [INCOME HISTORY]\n";
        Show_All_Transaction(this->incomes_transaction, this->inCount);
    }

    // 2. EXPENSE TABLE
    if (expCount > 0)
    {
        cout << "\n [EXPENSE HISTORY]\n";
        Show_All_Transaction(this->expenses_transaction, this->expCount);
    }

    if (inCount == 0 && expCount == 0)
    {
        cout << " [!] No transaction history found.\n";
    }
    cout << string(width, '-') << endl;
}

void User_Info::Show_Recurring_Transaction_List()
{
    // Define standard widths
    const int wDate = 14;
    const int wCat = 22;
    const int wWal = 18;
    const int wAmt = 15;

    cout << "\n";

    // 1. INCOME TABLE
    if (recur_trans_income_count > 0)
    {
        cout << "\n [RECURRING INCOME TRANSACTIONS]\n";
        Show_Recur_Transaction(this->Recurring_Transaction_Income_List, this->recur_trans_income_count);
    }

    // 2. EXPENSE TABLE
    if (recur_trans_expense_count > 0)
    {
        cout << "\n [RECURRING EXPENSE TRANSACTIONS]\n";
        Show_Recur_Transaction(this->Recurring_Transaction_Expense_List, this->recur_trans_expense_count);
    }

    if (recur_trans_expense_count == 0 && recur_trans_income_count == 0)
    {
        cout << " [!] No recurring transaction yet found.\n";
    }
    cout << string(width, '=') << endl;
}

// Add to User_Info.cpp

void User_Info::Show_Recurring_Transaction_List(Recurring_Transaction_Income**& p)
{
        // Define standard widths
    const int wDate = 14;
    const int wCat = 22;
    const int wWal = 18;
    const int wAmt = 15;

    cout << "\n";
    // EXPENSE TABLE
    if (recur_trans_expense_count > 0)
    {
        cout << "\n [RECURRING INCOME TRANSACTIONS]\n";
        Show_Recur_Transaction(this->Recurring_Transaction_Income_List, this->recur_trans_income_count);
    }

    if (recur_trans_income_count == 0)
    {
        cout << " [!] No recurring transaction yet found.\n";
    }
    cout << string(width, '=') << endl;
}
void User_Info::Show_Recurring_Transaction_List(Recurring_Transaction_Expense**& p)
{
        // Define standard widths
    const int wDate = 14;
    const int wCat = 22;
    const int wWal = 18;
    const int wAmt = 15;

    cout << "\n";

    // EXPENSE TABLE
    if (recur_trans_expense_count > 0)
    {
        cout << "\n [RECURRING EXPENSE TRANSACTIONS]\n";
        Show_Recur_Transaction(this->Recurring_Transaction_Expense_List, this->recur_trans_expense_count);
    }

    if (recur_trans_expense_count == 0)
    {
        cout << " [!] No recurring transaction yet found.\n";
    }
    cout << string(width, '=') << endl;
}
