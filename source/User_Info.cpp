#include "../header/User_Info.h"

void User_Info::resize()
{
    resize1(Wallet_List, wallet_count, wallet_capacity);
    resize1(expense, expense_count, expense_capacity);
    resize1(income, income_count, income_capacity);
    resize1(Recurring_Transaction_Expense_List, recur_trans_expense_count, recur_trans_expense_capacity);
    resize1(Recurring_Transaction_Income_List, recur_trans_income_count, recur_trans_income_capacity);
    resize1(incomes_transaction, inCount, inCap);
    resize1(expenses_transaction, expCount, expCap);
}

void User_Info::SaveToBinary(ofstream &out) 
{
    WriteString(out, name);
    out.write(reinterpret_cast<char *>(&this->default_Wallet->id), sizeof(int));

    // Output number of elements of each array
    out.write(reinterpret_cast<char *>(&this->income_count), sizeof(int));
    out.write(reinterpret_cast<char *>(&this->expense_count), sizeof(int));
    out.write(reinterpret_cast<char *>(&this->wallet_count), sizeof(int));
    out.write(reinterpret_cast<char *>(&this->recur_trans_income_count), sizeof(int));
    out.write(reinterpret_cast<char *>(&this->recur_trans_expense_count), sizeof(int));
    out.write(reinterpret_cast<char *>(&this->inCount), sizeof(int));
    out.write(reinterpret_cast<char *>(&this->expCount), sizeof(int));

    // Write the actual object info
    // Write transaction type;
    // income
    for (int i = 0; i < this->income_count; i++)
    {
        out.write(reinterpret_cast<char *>(&this->income[i]->id), sizeof(int));
        // name
        WriteString(out, this->income[i]->name);
    }
    // expense
    for (int i = 0; i < this->expense_count; i++)
    {
        out.write(reinterpret_cast<char *>(&this->expense[i]->id), sizeof(int));
        // name
        WriteString(out, this->expense[i]->name);
    }

    // Write Wallet;
    for (int i = 0; i < wallet_count; i++)
    {
        out.write(reinterpret_cast<char *>(&this->Wallet_List[i]->id), sizeof(int));
        // name
        WriteString(out, this->Wallet_List[i]->name);
        // bà lăng (balance)
        out.write(reinterpret_cast<char *>(&this->Wallet_List[i]->remain), sizeof(long long));
        out.write(reinterpret_cast<char *>(&this->Wallet_List[i]->inCount), sizeof(int));
        out.write(reinterpret_cast<char *>(&this->Wallet_List[i]->expCount), sizeof(int));
    }

    // Write Recur;
    // income
    for (int i = 0; i < this->recur_trans_income_count; i++)
    {
        // id
        out.write((char *)&this->Recurring_Transaction_Income_List[i]->id, sizeof(int));
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
    // expense
    for (int i = 0; i < this->recur_trans_expense_count; i++)
    {
        // id
        out.write((char *)&this->Recurring_Transaction_Expense_List[i]->id, sizeof(int));
        // date
        out.write((char *)&this->Recurring_Transaction_Expense_List[i]->start, sizeof(Date));
        out.write((char *)&this->Recurring_Transaction_Expense_List[i]->end, sizeof(Date));
        // id
        out.write((char *)&this->Recurring_Transaction_Expense_List[i]->type->id, sizeof(int));
        // Amount
        out.write((char *)&this->Recurring_Transaction_Expense_List[i]->amount, sizeof(long long));
        // Wallet
        out.write((char *)&this->Recurring_Transaction_Expense_List[i]->wallet->id, sizeof(int));
        // Desc
        WriteString(out, this->Recurring_Transaction_Expense_List[i]->description);
    }

    // Write Transaction;
    // income
    for (int i = 0; i < this->inCount; i++)
    {
        out.write((char *)&this->incomes_transaction[i]->id, sizeof(int));
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

    // expense
    for (int i = 0; i < this->expCount; i++)
    {
        out.write((char *)&this->expenses_transaction[i]->id, sizeof(int));
        // date
        out.write((char *)&this->expenses_transaction[i]->date, sizeof(Date));

        // id (Accessing the ID from the ExpenseCategory pointer)
        out.write((char *)&this->expenses_transaction[i]->type->id, sizeof(int));

        // Amount
        out.write((char *)&this->expenses_transaction[i]->amount, sizeof(long long));
        // Wallet
        out.write((char *)&this->expenses_transaction[i]->wallet->id, sizeof(int));

        // Desc
        WriteString(out, expenses_transaction[i]->description);
    }
}
void User_Info::LoadFromBinary(ifstream &out)
{
    ReadString(out, name);
    int default_Wallet_ID;
    out.read(reinterpret_cast<char *>(&default_Wallet_ID), sizeof(int));

    // Get baxk number of elements of each array
    out.read(reinterpret_cast<char *>(&this->income_count), sizeof(int));
    out.read(reinterpret_cast<char *>(&this->expense_count), sizeof(int));
    out.read(reinterpret_cast<char *>(&this->wallet_count), sizeof(int));
    out.read(reinterpret_cast<char *>(&this->recur_trans_income_count), sizeof(int));
    out.read(reinterpret_cast<char *>(&this->recur_trans_expense_count), sizeof(int));
    out.read(reinterpret_cast<char *>(&this->inCount), sizeof(int));
    out.read(reinterpret_cast<char *>(&this->expCount), sizeof(int));

    this->resize();

    // Read the actual object info
    // Read transaction type;
    // income
    for (int i = 0; i < this->income_count; i++)
    {
        this->income[i] = new IncomeSource;
        out.read(reinterpret_cast<char *>(&this->income[i]->id), sizeof(int));
        // name
        ReadString(out, this->income[i]->name);
    }
    // expense
    for (int i = 0; i < this->expense_count; i++)
    {
        this->expense[i] = new ExpenseCategory;
        out.read(reinterpret_cast<char *>(&this->expense[i]->id), sizeof(int));
        // name
        ReadString(out, this->expense[i]->name);
    }

    // Read Wallet;

    for (int i = 0; i < wallet_count; i++)
    {
        this->Wallet_List[i] = new Wallet;
        out.read(reinterpret_cast<char *>(&this->Wallet_List[i]->id), sizeof(int));
        if(this->Wallet_List[i]->id == default_Wallet_ID)
        {
            default_Wallet=this->Wallet_List[i];
        }
        // name
        ReadString(out, this->Wallet_List[i]->name);
        // bà lăng (balance)
        out.read(reinterpret_cast<char *>(&this->Wallet_List[i]->remain), sizeof(long long));
        int tempIn, tempExp;
        out.read(reinterpret_cast<char *>(&tempIn), sizeof(int));
        out.read(reinterpret_cast<char *>(&tempExp), sizeof(int));
        this->Wallet_List[i]->inCount = tempIn;
        this->Wallet_List[i]->expCount = tempExp;
        this->Wallet_List[i]->Wallet_resize();
        this->Wallet_List[i]->inCount = 0;
        this->Wallet_List[i]->expCount = 0;

    }

    // Read Recur
    //  Read Recur Income
    for (int i = 0; i < this->recur_trans_income_count; i++)
    {
        this->Recurring_Transaction_Income_List[i] = new Recurring_Transaction_Income;

        // Date
        out.read((char *)&this->Recurring_Transaction_Income_List[i]->id, sizeof(int));
        out.read((char *)&this->Recurring_Transaction_Income_List[i]->start, sizeof(Date));
        out.read((char *)&this->Recurring_Transaction_Income_List[i]->end, sizeof(Date));

        // Type (IncomeSource) - Dummy Link
        IncomeSource *dummy_type = new IncomeSource;
        this->Recurring_Transaction_Income_List[i]->type = dummy_type;
        out.read((char *)&this->Recurring_Transaction_Income_List[i]->type->id, sizeof(int));

        // Amount
        out.read((char *)&this->Recurring_Transaction_Income_List[i]->amount, sizeof(long long));

        // Wallet - Dummy Link
        Wallet *dummy_wallet = new Wallet;
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
        out.read((char *)&this->Recurring_Transaction_Expense_List[i]->id, sizeof(int));
        out.read((char *)&this->Recurring_Transaction_Expense_List[i]->start, sizeof(Date));
        out.read((char *)&this->Recurring_Transaction_Expense_List[i]->end, sizeof(Date));

        // Type (ExpenseCategory) - Dummy Link
        ExpenseCategory *dummy_type = new ExpenseCategory;
        this->Recurring_Transaction_Expense_List[i]->type = dummy_type;
        out.read((char *)&this->Recurring_Transaction_Expense_List[i]->type->id, sizeof(int));

        // Amount
        out.read((char *)&this->Recurring_Transaction_Expense_List[i]->amount, sizeof(long long));

        // Wallet - Dummy Link
        Wallet *dummy_wallet = new Wallet;
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
    // Must Link to Wallet and type

    // Read Transaction;
    // income
    for (int i = 0; i < this->inCount; i++)
    {

        this->incomes_transaction[i] = new Transaction_Income;
        // id
        out.read((char *)&this->incomes_transaction[i]->id, sizeof(int));
        // date
        out.read((char *)&this->incomes_transaction[i]->date, sizeof(Date));
        // id -> create dummy object
        IncomeSource *dummy_trans = new IncomeSource;
        this->incomes_transaction[i]->type = dummy_trans;
        out.read((char *)&this->incomes_transaction[i]->type->id, sizeof(int));
        // Amount
        out.read((char *)&this->incomes_transaction[i]->amount, sizeof(long long));
        // Wallet
        Wallet *dummy_wallet = new Wallet;
        this->incomes_transaction[i]->wallet = dummy_wallet;
        out.read((char *)&this->incomes_transaction[i]->wallet->id, sizeof(int));
        //  Desc
        ReadString(out, this->incomes_transaction[i]->description);
        // Link Transaction type
        Find_By_ID(this->incomes_transaction[i]->type->id, this->income, this->income_count, this->incomes_transaction[i]->type);
        delete dummy_trans;
        Find_By_ID(this->incomes_transaction[i]->wallet->id, this->Wallet_List, this->wallet_count, this->incomes_transaction[i]->wallet);
        delete dummy_wallet;
        // Wallet Linking back
        this->incomes_transaction[i]->wallet->Wallet_resize();
        this->incomes_transaction[i]->wallet->incomes[this->incomes_transaction[i]->wallet->inCount] = this->incomes_transaction[i];
        this->incomes_transaction[i]->wallet->inCount += 1;
    }

    // Read Transaction Expense
    for (int i = 0; i < this->expCount; i++)
    {
        this->expenses_transaction[i] = new Transaction_Expense;

        // id
        out.read((char *)&this->expenses_transaction[i]->id, sizeof(int));
        // Date
        out.read((char *)&this->expenses_transaction[i]->date, sizeof(Date));

        // Type (ExpenseCategory) - Dummy Link
        ExpenseCategory *dummy_type = new ExpenseCategory;
        this->expenses_transaction[i]->type = dummy_type;
        out.read((char *)&this->expenses_transaction[i]->type->id, sizeof(int));

        // Amount
        out.read((char *)&this->expenses_transaction[i]->amount, sizeof(long long));

        // Wallet - Dummy Link
        Wallet *dummy_wallet = new Wallet;
        this->expenses_transaction[i]->wallet = dummy_wallet;
        out.read((char *)&this->expenses_transaction[i]->wallet->id, sizeof(int));

        // Description
        ReadString(out, expenses_transaction[i]->description);

        // Linking
        Find_By_ID(this->expenses_transaction[i]->type->id, this->expense, this->expense_count, this->expenses_transaction[i]->type);
        delete dummy_type;
        Find_By_ID(this->expenses_transaction[i]->wallet->id, this->Wallet_List, this->wallet_count, this->expenses_transaction[i]->wallet);
        delete dummy_wallet;

        // Wallet linking back
        this->expenses_transaction[i]->wallet->Wallet_resize();
        this->expenses_transaction[i]->wallet->expenses[this->expenses_transaction[i]->wallet->expCount] = this->expenses_transaction[i];
        this->expenses_transaction[i]->wallet->expCount += 1;
    }
    Sort_By_Date_Transaction(incomes_transaction, inCount);
    Sort_By_Date_Transaction(expenses_transaction, expCount);
    // Must Link to Wallet and type
}



// --- Bổ sung vào User_Info.cpp ---
// --- Helper to ensure uniform date spacing (10 chars + 2 padding) ---





bool User_Info::check_recur_trans(Recurring_Transaction_Expense *&p, Date current_date)
{
    // 1. Validate pointers
    if (!p || !p->wallet || !p->type)
        return false;

    bool has_changes = false;
    Date iterator_date = p->start; // Start checking from the recurring start date
    Date end_date=p->end;
    if(Date_Less_Or_Equal(current_date, p->end))
    {
        end_date=current_date;
    }

    // 2. Loop month-by-month until we pass the current date
    while (Date_Less_Or_Equal(iterator_date, end_date))
    {


        // 3. CHECK: Has this transaction already been generated for this specific Month/Year?
        bool already_exists = false;

        // Scan the existing expense history
        for (int i = 0; i < p->wallet->expCount; i++)
        {
            // Check if this wallet already has this recurring transaction for this month/year
            if (p->wallet->expenses[i]->id == p->id &&
                p->wallet->expenses[i]->date.month == iterator_date.month &&
                p->wallet->expenses[i]->date.year == iterator_date.year &&
                p->wallet->expenses[i]->type->id == p->type->id &&
                p->wallet->expenses[i]->amount == p->amount)
            {
                already_exists = true;
                break;
            }
        }

        // 4. GENERATE: If not found, create the transaction for the 1st of that month
        if (!already_exists)
        {
            this->resize(); // Ensure array has space

            // Create new transaction object
            expenses_transaction[expCount] = new Transaction_Expense;

            // Set Date to 1st of the month (as requested)
            this->expenses_transaction[expCount]->id = p->id;
            expenses_transaction[expCount]->date.day = iterator_date.day;
            expenses_transaction[expCount]->date.month = iterator_date.month;
            expenses_transaction[expCount]->date.year = iterator_date.year;

            // Copy details from Recurring template
            expenses_transaction[expCount]->amount = p->amount;
            expenses_transaction[expCount]->type = p->type;     // Pointer copy
            expenses_transaction[expCount]->wallet = p->wallet; // Pointer copy

            // Generate a description so user knows it was automated
            expenses_transaction[expCount]->description = "(Auto-Generated for ID "+to_string(expenses_transaction[expCount]->id)+")" + p->description;

            // 5. UPDATE WALLET BALANCE
            p->wallet->remain -= p->amount;

            // Link transaction to Wallet's internal list
            p->wallet->Wallet_resize();
            p->wallet->expenses[p->wallet->expCount] = expenses_transaction[expCount];
            p->wallet->expCount++;

            // Increment User_Info global count
            this->expCount++;
            has_changes = true;

            cout << " [Auto] Generated recurring expense for ID "<<p->id<<" : "
                 << iterator_date.month << "/" << iterator_date.year << endl;
        }

        // 6. ADVANCE TIME: Move iterator to the next month
        iterator_date.month++;
        if (iterator_date.month > 12)
        {
            iterator_date.month = 1;
            iterator_date.year++;
        }
    }

    // Sort list by date again to keep history tidy
    if (has_changes)
    {
        Sort_By_Date_Transaction(expenses_transaction, expCount);
    }

    return has_changes;
}

bool User_Info::check_recur_trans(Recurring_Transaction_Income *&p, Date current_date)
{
    // 1. Validate pointers
    if (!p || !p->wallet || !p->type)
        return false;

    bool has_changes = false;
    Date iterator_date = p->start;
    Date end_date=p->end;
    if(Date_Less_Or_Equal(current_date, p->end))
    {
        end_date=current_date;
    }

    // 2. Loop month-by-month until we pass the current date
    while (Date_Less_Or_Equal(iterator_date, end_date))
    {

        // 3. CHECK: Has this transaction already been generated?
        bool already_exists = false;

        // Scan the existing INCOME history
        for (int i = 0; i < p->wallet->inCount; i++)
        {
            // Logic: ID matches Recurring Rule ID, plus matching Date/Type/Wallet/Amount
            if (p->wallet->incomes[i]->id == p->id &&
                p->wallet->incomes[i]->date.month == iterator_date.month &&
                p->wallet->incomes[i]->date.year == iterator_date.year &&
                p->wallet->incomes[i]->type->id == p->type->id &&
                //p->wallet->incomes[i]->wallet->id == p->wallet->id &&
                p->wallet->incomes[i]->amount == p->amount)
            {
                already_exists = true;
                break;
            }
        }

        // 4. GENERATE: If not found, create the transaction
        if (!already_exists)
        {
            this->resize();

            // Create new transaction object
            incomes_transaction[inCount] = new Transaction_Income;

            // Link ID to the Recurring Rule ID (as per your fix)
            incomes_transaction[inCount]->id = p->id;

            // Set Date
            incomes_transaction[inCount]->date.day = iterator_date.day;
            incomes_transaction[inCount]->date.month = iterator_date.month;
            incomes_transaction[inCount]->date.year = iterator_date.year;

            // Copy details
            incomes_transaction[inCount]->amount = p->amount;
            incomes_transaction[inCount]->type = p->type;
            incomes_transaction[inCount]->wallet = p->wallet;
            incomes_transaction[inCount]->description = "(Auto-Generated)" + p->description;

            // 5. UPDATE WALLET BALANCE (ADDITION for Income)
            p->wallet->remain += p->amount;

            // Link transaction to Wallet's internal list
            p->wallet->Wallet_resize();
            p->wallet->incomes[p->wallet->inCount] = incomes_transaction[inCount];
            p->wallet->inCount++;

            // Increment User_Info global count
            this->inCount++;
            has_changes = true;

            cout << " [Auto] Generated recurring expense for ID "<<p->id<<" : "
                 << iterator_date.month << "/" << iterator_date.year << endl;
        }

        // 6. ADVANCE TIME
        iterator_date.month++;
        if (iterator_date.month > 12)
        {
            iterator_date.month = 1;
            iterator_date.year++;
        }
    }

    // Sort list by date to keep history tidy
    if (has_changes)
    {
        Sort_By_Date_Transaction(incomes_transaction, inCount);
    }

    return has_changes;
}

void User_Info::Stop_recur_trans(Recurring_Transaction_Expense*& p)
{
    int id;
    string input;
    bool check=true;
    Recurring_Transaction_Expense *dummy;
    while(check)
    {
    cout << "Enter Recurring Transaction Expense ID to stop: ";
    cin>>input;
    
    if (!isValidInt(input))
    {
        Clear_Buffer();
        cout << "Error: Please Input an valid ID.\n";
        cout << "Press enter to retype...";
        cin.get();
        Clear_Buffer();
        ClearLines(3);
    }
    else
    {
        id=stoi(input);
        if(!Find_By_ID(id, Recurring_Transaction_Expense_List, recur_trans_expense_count, dummy))
        {
            cout << "Error: Please Input an valid ID.\n";
            system("pause");
            return;
        }
        else
        check=false;
    }
    }
    Clear_Buffer();
    dummy->end.day=0;
    dummy->end.month=0;
    dummy->end.year=0;
    Date pin;
    GetCurrentDate(pin);
    dummy->description="Deleted on " + Date_to_string(pin);
    cout << "Stop recurring transaction with ID "<<id<<" successfully.\n";
    system("pause");
}
void User_Info::Stop_recur_trans(Recurring_Transaction_Income*& p)
{
    int id;
    string input;
    bool check=true;
    Recurring_Transaction_Income *dummy;
    while(check)
    {
    cout << "Enter Recurring Transaction Income ID to stop: ";
    cin>>input;
    
    if (!isValidInt(input))
    {
        Clear_Buffer();
        cout << "Error: Please Input an valid ID.\n";
        cout << "Press enter to retype...";
        cin.get();
        Clear_Buffer();
        ClearLines(3);
    }
    else
    {
        id=stoi(input);
        if(!Find_By_ID(id, Recurring_Transaction_Income_List, recur_trans_income_count, dummy))
        {
            cout << "Error: Please Input an valid ID.\n";
            system("pause");
            return;
        }
        else
        check=false;
    }
    }
    Clear_Buffer();
    dummy->end.day=0;
    dummy->end.month=0;
    dummy->end.year=0;
    Date pin;
    GetCurrentDate(pin);
    dummy->description="Deleted on " + Date_to_string(pin);
    cout << "Stop recurring transaction with ID "<<id<<" successfully.\n";
    system("pause");
}


// Search for a Wallet by name
Wallet *User_Info::Choose_Wallet(string name)
{
    for (int i = 0; i < this->wallet_count; i++)
    {
        // Check if pointer is valid before accessing name (safety check)
        if (this->Wallet_List[i] && compare_string(name, this->Wallet_List[i]->name))
        {
            return this->Wallet_List[i];
        }
    }
    return nullptr; // Return NULL if not found
}

// Search for an Income Source by name
IncomeSource *User_Info::Choose_IS(string name)
{
    for (int i = 0; i < this->income_count; i++)
    {
        if (this->income[i] && compare_string(name, this->income[i]->name))
        {
            return this->income[i];
        }
    }
    return nullptr; // Return NULL if not found
}

// Search for an Expense Category by name
ExpenseCategory *User_Info::Choose_EC(string name)
{
    for (int i = 0; i < this->expense_count; i++)
    {
        if (this->expense[i] && compare_string(name, this->expense[i]->name))
        {
            return this->expense[i];
        }
    }
    return nullptr; // Return NULL if not found
}

//
//
//
//
//
//

//
//
//
//
//
//
//
//
// check ví và data có nên xóa
