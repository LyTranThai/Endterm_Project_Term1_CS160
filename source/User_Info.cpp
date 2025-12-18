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
            //income
            for(int i=0; i<this->income_count; i++)
            {
                out.write(reinterpret_cast<char*>(&this->income[i]->id), sizeof(int));
                // name
                WriteString(out,this->income[i]->name);
            }
            //expense
            for(int i=0; i<this->expense_count; i++)
            {
                out.write(reinterpret_cast<char*>(&this->expense[i]->id), sizeof(int));
                // name
                WriteString(out,this->expense[i]->name);
            }

        //Write Wallet;
            for(int i=0; i<wallet_count; i++)
            {
                out.write(reinterpret_cast<char*>(&this->Wallet_List[i]->id), sizeof(int));
                // name
                WriteString(out, this->Wallet_List[i]->name);
                // bà lăng (balance)
                out.write(reinterpret_cast<char*>(&this->Wallet_List[i]->remain), sizeof(long long));
                out.write(reinterpret_cast<char*>(&this->Wallet_List[i]->inCount), sizeof(int));
                out.write(reinterpret_cast<char*>(&this->Wallet_List[i]->expCount), sizeof(int));
            }


        //Write Recur;
            //income
            for (int i = 0; i < this->recur_trans_income_count; i++)
            {
                // date
                out.write((char *)&this->Recurring_Transaction_Income_List[i]->start, sizeof(Date));
                out.write((char *)&this->Recurring_Transaction_Income_List[i]->end, sizeof(Date));
                // id
                out.write((char *)&this->Recurring_Transaction_Income_List[i]->type->id, sizeof(int));
                // Amount
                out.write((char *)&this->Recurring_Transaction_Income_List[i]->amount, sizeof(long long));
                //  Desc
                WriteString(out, this->Recurring_Transaction_Income_List[i]->description);
            }
        //expense
            for (int i = 0; i < this->recur_trans_expense_count; i++)
            {
                //date
                out.write((char *)&this->Recurring_Transaction_Expense_List[i]->start, sizeof(Date));
                out.write((char *)&this->Recurring_Transaction_Expense_List[i]->end, sizeof(Date));
                //id
                out.write((char *)&this->Recurring_Transaction_Expense_List[i]->type->id, sizeof(int));
                // Amount
                out.write((char *)&this->Recurring_Transaction_Expense_List[i]->amount, sizeof(long long));
                // Desc
                WriteString(out, this->Recurring_Transaction_Income_List[i]->description);
            }


        //Write Transaction;
        //income
            for (int i = 0; i < this->inCount; i++)
            {

                // date
                out.write((char *)&this->incomes_transaction[i]->date, sizeof(Date));
                // id
                out.write((char *)&this->incomes_transaction[i]->type->id, sizeof(int));
                // Amount
                out.write((char *)&this->incomes_transaction[i]->amount, sizeof(long long));
                //  Desc
                WriteString(out, this->incomes_transaction[i]->description);
            }



        //expense
            for (int i = 0; i < this->expCount; i++)
            {
                // date
                out.write((char *)&this->expenses_transaction[i]->date, sizeof(Date));
                
                // id (Accessing the ID from the ExpenseCategory pointer)
                out.write((char *)&this->expenses_transaction[i]->type->id, sizeof(int));
                
                // Amount
                out.write((char *)&this->expenses_transaction[i]->amount, sizeof(long long));
                
                // Desc
                WriteString(out, expenses_transaction[i]->description);
            }

        
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