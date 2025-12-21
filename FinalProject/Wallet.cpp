
#include "Wallet.h"
#include "DataHandling.h"

bool Wallet::Input_Wallet(string info)
{
    cout << "Enter Wallet Name: ";
    if (cin.peek() == '\n')
        cin.ignore();
    getline(cin, this->name);

    cout << "Enter Initial Balance: ";
    cin >> this->remain;
    return true;
}

void Wallet::Output_Terminal()
{
    cout << "ID: " << id
         << " | Name: " << name
         << " | Balance: " << remain << endl;
}

void Wallet::SaveToBinary(string filename)
{

    ofstream out(filename, ios::binary | ios::app);
    if (out.is_open())
    {
        out.write((char *)&id, sizeof(int));
        WriteString(out, name);
        out.write((char *)&remain, sizeof(long long));
        out.close();
    }
}

void Wallet::Wallet_resize()
{

    if (inCount >= inCap)
    {
        int newCap = inCap * 2;
        Transaction_Income **newItem = new Transaction_Income *[newCap];
        for (int i = 0; i < inCount; i++)
            newItem[i] = incomes[i];
        delete[] incomes;
        incomes = newItem;
        inCap = newCap;
    }

    if (expCount >= expCap)
    {
        int newCap = expCap * 2;
        Transaction_Expense **newItem = new Transaction_Expense *[newCap];
        for (int i = 0; i < expCount; i++)
            newItem[i] = expenses[i];
        delete[] expenses;
        expenses = newItem;
        expCap = newCap;
    }
}