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
                // Wallet
                out.write((char *)&this->Recurring_Transaction_Income_List[i]->wallet->id, sizeof(int));
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
                //Wallet
                out.write((char *)&this->Recurring_Transaction_Expense_List[i]->wallet->id, sizeof(int));
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
                // Wallet
                out.write((char *)&this->incomes_transaction[i]->wallet->id, sizeof(int));
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
                //Wallet
                out.write((char *)&this->expenses_transaction[i]->wallet->id, sizeof(int));
                
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

        //Read the actual object info
        //Read transaction type;
            //income
            for(int i=0; i<this->income_count; i++)
            {
                this->income[i]=new IncomeSource;
                out.read(reinterpret_cast<char*>(&this->income[i]->id), sizeof(int));
                // name
                ReadString(out,this->income[i]->name);
            }
            //expense
            for(int i=0; i<this->expense_count; i++)
            {
                this->expense[i]=new ExpenseCategory;
                out.read(reinterpret_cast<char*>(&this->expense[i]->id), sizeof(int));
                // name
                ReadString(out,this->expense[i]->name);
            }
        
        
        //Read Wallet;
            
            for(int i=0; i<wallet_count; i++)
            {
                this->Wallet_List[i]=new Wallet;
                out.read(reinterpret_cast<char*>(&this->Wallet_List[i]->id), sizeof(int));
                // name
                ReadString(out, this->Wallet_List[i]->name);
                // bà lăng (balance)
                out.read(reinterpret_cast<char*>(&this->Wallet_List[i]->remain), sizeof(long long));
                out.read(reinterpret_cast<char*>(&this->Wallet_List[i]->inCount), sizeof(int));
                out.read(reinterpret_cast<char*>(&this->Wallet_List[i]->expCount), sizeof(int));
                this->Wallet_List[i]->Wallet_resize();
            }
        
        //Read Recur
        // Read Recur Income
            for (int i = 0; i < this->recur_trans_income_count; i++)
            {
                this->Recurring_Transaction_Income_List[i] = new Recurring_Transaction_Income;
                
                // Date
                out.read((char *)&this->Recurring_Transaction_Income_List[i]->start, sizeof(Date));
                out.read((char *)&this->Recurring_Transaction_Income_List[i]->end, sizeof(Date));
                
                // Type (IncomeSource) - Dummy Link
                IncomeSource* dummy_type = new IncomeSource;
                this->Recurring_Transaction_Income_List[i]->type = dummy_type;
                out.read((char *)&this->Recurring_Transaction_Income_List[i]->type->id, sizeof(int));
                
                // Amount
                out.read((char *)&this->Recurring_Transaction_Income_List[i]->amount, sizeof(long long));
                
                // Wallet - Dummy Link
                Wallet* dummy_wallet = new Wallet;
                this->Recurring_Transaction_Income_List[i]->wallet = dummy_wallet;
                out.read((char *)&this->Recurring_Transaction_Income_List[i]->wallet->id, sizeof(int));
                // Description
                ReadString(out, this->Recurring_Transaction_Income_List[i]->description);
                // Linking
                Find_By_ID(this->Recurring_Transaction_Income_List[i]->type->id, this->income, this->income_count, this->Recurring_Transaction_Income_List[i]->type);
                delete dummy_type;
                Find_By_ID(this->Recurring_Transaction_Income_List[i]->wallet->id, this->Wallet_List, this->wallet_count, this->Recurring_Transaction_Income_List[i]->wallet);
                delete dummy_wallet;
            }

        // Read Recur Expense
            for (int i = 0; i < this->recur_trans_expense_count; i++)
            {
                this->Recurring_Transaction_Expense_List[i] = new Recurring_Transaction_Expense;
                
                // Date
                out.read((char *)&this->Recurring_Transaction_Expense_List[i]->start, sizeof(Date));
                out.read((char *)&this->Recurring_Transaction_Expense_List[i]->end, sizeof(Date));
                
                // Type (ExpenseCategory) - Dummy Link
                ExpenseCategory* dummy_type = new ExpenseCategory;
                this->Recurring_Transaction_Expense_List[i]->type = dummy_type;
                out.read((char *)&this->Recurring_Transaction_Expense_List[i]->type->id, sizeof(int));
                
                // Amount
                out.read((char *)&this->Recurring_Transaction_Expense_List[i]->amount, sizeof(long long));

                // Wallet - Dummy Link
                Wallet* dummy_wallet = new Wallet;
                this->Recurring_Transaction_Expense_List[i]->wallet = dummy_wallet;
                out.read((char *)&this->Recurring_Transaction_Expense_List[i]->wallet->id, sizeof(int));
                
                // Description
                ReadString(out, this->Recurring_Transaction_Expense_List[i]->description);

                // Linking
                Find_By_ID(this->Recurring_Transaction_Expense_List[i]->type->id, this->expense, this->expense_count, this->Recurring_Transaction_Expense_List[i]->type);
                delete dummy_type;

                Find_By_ID(this->Recurring_Transaction_Expense_List[i]->wallet->id, this->Wallet_List, this->wallet_count, this->Recurring_Transaction_Expense_List[i]->wallet);
                delete dummy_wallet;
            }
        //Must Link to Wallet and type

        //Read Transaction;
        //income
            for (int i = 0; i < this->inCount; i++)
            {
                this->incomes_transaction[i]=new Transaction_Income;
                // date
                out.read((char *)&this->incomes_transaction[i]->date, sizeof(Date));
                // id -> create dummy object
                IncomeSource* dummy_trans =new IncomeSource;
                this->incomes_transaction[i]->type= dummy_trans;
                out.read((char *)&this->incomes_transaction[i]->type->id, sizeof(int));
                // Amount
                out.read((char *)&this->incomes_transaction[i]->amount, sizeof(long long));
                // Wallet
                Wallet* dummy_wallet= new Wallet;
                this->incomes_transaction[i]->wallet = dummy_wallet;
                out.read((char *)&this->incomes_transaction[i]->wallet->id, sizeof(int));                
                //  Desc
                ReadString(out, this->incomes_transaction[i]->description);
                //Link Transaction type
                Find_By_ID(this->incomes_transaction[i]->type->id, this->income, this->income_count,  this->incomes_transaction[i]->type);
                delete dummy_trans;
                Find_By_ID(this->incomes_transaction[i]->wallet->id, this->Wallet_List, this->wallet_count, this->incomes_transaction[i]->wallet);
                delete dummy_wallet;
            }


        // Read Transaction Expense
            for (int i = 0; i < this->expCount; i++)
            {
                this->expenses_transaction[i] = new Transaction_Expense;
                
                // Date
                out.read((char *)&this->expenses_transaction[i]->date, sizeof(Date));
                
                // Type (ExpenseCategory) - Dummy Link
                ExpenseCategory* dummy_type = new ExpenseCategory;
                this->expenses_transaction[i]->type = dummy_type;
                out.read((char *)&this->expenses_transaction[i]->type->id, sizeof(int));
                
                // Amount
                out.read((char *)&this->expenses_transaction[i]->amount, sizeof(long long));

                // Wallet - Dummy Link
                Wallet* dummy_wallet = new Wallet;
                this->expenses_transaction[i]->wallet = dummy_wallet;
                out.read((char *)&this->expenses_transaction[i]->wallet->id, sizeof(int));
                
                // Description
                ReadString(out, expenses_transaction[i]->description);

                // Linking
                Find_By_ID(this->expenses_transaction[i]->type->id, this->expense, this->expense_count, this->expenses_transaction[i]->type);
                delete dummy_type;
                Find_By_ID(this->expenses_transaction[i]->wallet->id, this->Wallet_List, this->wallet_count, this->expenses_transaction[i]->wallet);
                delete dummy_wallet;
            }

        //Must Link to Wallet and type

    }


