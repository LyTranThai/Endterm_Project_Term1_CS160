#include "..\header\User_Info.h"


    void User_Info::resize()
    {
        resize1(Wallet_List,wallet_count,wallet_capacity);
        resize1(expense,expense_count,expense_capacity);
        resize1(income,income_count,income_capacity);
        resize1(Recurring_Transaction_Expense_List,recur_trans_expense_count,recur_trans_expense_capacity);
        resize1(Recurring_Transaction_Income_List,recur_trans_income_count,recur_trans_income_capacity);
        resize1(incomes_transaction,inCount,inCap);
        resize1(expenses_transaction,expCount,expCap);
    }

    template <typename T>
    void resize1(T** & p, int size, int cap)
    {
        while(size>=cap)
        {
            cap *= 2;
            
        }
        T**dummy=p;
        p= new T*[cap];
        for(int i=0; i<size; i++)
        {
            p[i]=dummy[i];
        }
        delete[]dummy;
    }

    void User_Info::SaveToBinary(ofstream& out,string filename)
    {
        WriteString(out,name);
        out.write(reinterpret_cast<char*>(&this->default_Wallet->id),sizeof(int));

        //Output number of elements of each array
        out.write(reinterpret_cast<char*>(&this->income_count),sizeof(int));
        out.write(reinterpret_cast<char*>(&this->expense_count),sizeof(int));
        out.write(reinterpret_cast<char*>(&this->wallet_count),sizeof(int));
        out.write(reinterpret_cast<char*>(&this->recur_trans_income_count),sizeof(int));
        out.write(reinterpret_cast<char*>(&this->recur_trans_expense_count),sizeof(int));
        out.write(reinterpret_cast<char*>(&this->inCount),sizeof(int));
        out.write(reinterpret_cast<char*>(&this->expCount),sizeof(int));

        
        //Write the actual object info
        //Write transaction type;
        //Write Wallet;
        //Write Recur;
        //Write Transaction;




        
    }
    void User_Info::LoadFromBinary(ifstream& out,string filename)
    {
        ReadString(out,name);
        out.read(reinterpret_cast<char*>(&this->default_Wallet->id),sizeof(int));

        //Get baxk number of elements of each array
        out.read(reinterpret_cast<char*>(&this->income_count),sizeof(int));
        out.read(reinterpret_cast<char*>(&this->expense_count),sizeof(int));
        out.read(reinterpret_cast<char*>(&this->wallet_count),sizeof(int));
        out.read(reinterpret_cast<char*>(&this->recur_trans_income_count),sizeof(int));
        out.read(reinterpret_cast<char*>(&this->recur_trans_expense_count),sizeof(int));
        out.read(reinterpret_cast<char*>(&this->inCount),sizeof(int));
        out.read(reinterpret_cast<char*>(&this->expCount),sizeof(int));

        this->resize();
        
    }