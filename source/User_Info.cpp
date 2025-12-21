#include "..\header\User_Info.h"

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

void User_Info::SaveToBinary(ofstream &out, string filename)
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
        WriteString(out, this->Recurring_Transaction_Income_List[i]->description);
    }

    // Write Transaction;
    // income
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

    // expense
    for (int i = 0; i < this->expCount; i++)
    {
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
void User_Info::LoadFromBinary(ifstream &out, string filename)
{
    ReadString(out, name);
    out.read(reinterpret_cast<char *>(&this->default_Wallet->id), sizeof(int));

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
        // name
        ReadString(out, this->Wallet_List[i]->name);
        // bà lăng (balance)
        out.read(reinterpret_cast<char *>(&this->Wallet_List[i]->remain), sizeof(long long));
        out.read(reinterpret_cast<char *>(&this->Wallet_List[i]->inCount), sizeof(int));
        out.read(reinterpret_cast<char *>(&this->Wallet_List[i]->expCount), sizeof(int));
        this->Wallet_List[i]->Wallet_resize();
    }

    // Read Recur
    //  Read Recur Income
    for (int i = 0; i < this->recur_trans_income_count; i++)
    {
        this->Recurring_Transaction_Income_List[i] = new Recurring_Transaction_Income;

        // Date
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
    }

    // Read Transaction Expense
    for (int i = 0; i < this->expCount; i++)
    {
        this->expenses_transaction[i] = new Transaction_Expense;

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
    }

    // Must Link to Wallet and type
}

void Show_Recurring_Transaction_List();
void User_Info::Add_Wallet()
{
    Wallet dummy;
    this->resize();
    while (true)
    {
        cout << "Enter your new wallet name: ";
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, dummy.name);

        if (dummy.name.empty() || check_string(dummy.name, '^'))
        {
            cout << "Invalid name (cannot be empty or contain '^'). Try again.\n";
            continue;
        }

        Wallet *save = nullptr;
        // Check for duplicate name
        if (Find_By_Name(dummy.name, this->Wallet_List, this->wallet_count, save))
        {
            cout << "Wallet name existed, please choose another name.\n";
        }
        else
        {
            break; // Name is valid and unique
        }
    }

    // Loop for Balance Input (Robust check)
    string s;
    long long validBalance = 0;
    while (true)
    {
        cout << "Enter your balance: ";
        cin >> s; // No spaces allowed in numbers, so cin is fine here

        // Use your existing helper
        if (isValidLongLong(s))
        {
            validBalance = stoll(s);
            break;
        }
        else
        {
            cout << "Invalid amount. Please enter a valid integer number.\n";
        }
    }

    // 4. GENERATE ID automatically
    // It scans existing wallets to find the highest ID and adds 1
    int new_id = Generate_ID(this->Wallet_List, this->wallet_count);

    // 5. Save to List
    Wallet_List[wallet_count] = new Wallet;
    Wallet_List[wallet_count]->id = new_id; // Assign the auto-generated ID
    Wallet_List[wallet_count]->name = dummy.name;
    Wallet_List[wallet_count]->remain = validBalance;

    wallet_count += 1;

    cout << "---------------------------------" << endl;
    cout << " New Wallet Created Successfully " << endl;
    cout << " ID:      " << new_id << endl;
    cout << " Name:    " << dummy.name << endl;
    cout << " Balance: " << validBalance << endl;
    cout << "---------------------------------" << endl;
}

void User_Info::Add_Expense()
{

    this->resize(); // Ensure capacity exists
    string new_name;

    // --- INPUT LOOP ---
    while (true)
    {
        cout << "Enter new expense category name (e.g., Food): ";

        // Clear buffer if needed to allow spaces in name
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, new_name);

        // Validation 1: Empty or Invalid Char
        if (new_name.empty() || check_string(new_name, '^'))
        {
            cout << "Invalid name. Cannot be empty or contain '^'. Try again.\n";
            continue;
        }

        // Validation 2: Duplicates
        ExpenseCategory *temp = nullptr;
        // Using Find_By_Name from DataHandling.h
        if (Find_By_Name(new_name, this->expense, this->expense_count, temp))
        {
            cout << "This category already exists! Please enter a different name.\n";
        }
        else
        {
            break; // Name is valid and unique
        }
    }

    // --- AUTO ID GENERATION ---
    // Uses the helper function to find max ID + 1
    int new_id = Generate_ID(this->expense, this->expense_count);

    // --- SAVE TO ARRAY ---
    this->expense[this->expense_count] = new ExpenseCategory;
    this->expense[this->expense_count]->id = new_id;
    this->expense[this->expense_count]->name = new_name;

    this->expense_count++;

    // --- OUTPUT FEEDBACK ---
    cout << "---------------------------------" << endl;
    cout << " New Expense Category Added: " << new_name << endl;
    cout << " ID Assigned: " << new_id << endl;
    cout << "---------------------------------" << endl;
}
void User_Info::Add_Income()
{
    this->resize(); // Ensure capacity exists
    string new_name;

    // --- INPUT LOOP ---
    while (true)
    {
        cout << "Enter new income source name (e.g., Salary): ";

        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, new_name);

        if (new_name.empty() || check_string(new_name, '^'))
        {
            cout << "Invalid name. Cannot be empty or contain '^'. Try again.\n";
            continue;
        }

        IncomeSource *temp = nullptr;
        // Using Find_By_Name to check duplicates in the income array
        if (Find_By_Name(new_name, this->income, this->income_count, temp))
        {
            cout << "This source already exists! Please enter a different name.\n";
        }
        else
        {
            break;
        }
    }

    // --- AUTO ID GENERATION ---
    int new_id = Generate_ID(this->income, this->income_count);

    // --- SAVE TO ARRAY ---
    this->income[this->income_count] = new IncomeSource;
    this->income[this->income_count]->id = new_id;
    this->income[this->income_count]->name = new_name;

    this->income_count++;

    // --- OUTPUT FEEDBACK ---
    cout << "---------------------------------" << endl;
    cout << " New Income Source Added: " << new_name << endl;
    cout << " ID Assigned: " << new_id << endl;
    cout << "---------------------------------" << endl;
}

void User_Info::Add_Expense_Transaction()
{
}
void User_Info::Add_Income_Transaction()
{
    string dateStr;
    // DATE
    Date transDate;
    // --- INPUT LOOP TO GET DATE---
    do
    {
        cout << "Enter Date of transaction (dd/mm/yyyy): ";
        getline(cin, dateStr);
        transDate = InputDate(dateStr);

        if (transDate.day == 0)
        {
            cout << "Invalid date format or logic! Please try again (e.g., 25/12/2023).\n";
        }
    } while (transDate.day == 0);

    string type_name;
    // INCOME SOURCE POINTER
    IncomeSource *dummy_IS = nullptr;
    int choice;
    bool check_IS = true;
    // --- INPUT LOOP TO GET INCOME SOURCE---
    while (check_IS)
    {
        while (true)
        {
            cout << "Enter your income source name (e.g., Salary): ";
            // Show_Income_Source();
            // This will draw all the Incomsource on for user to choose
            if (cin.peek() == '\n')
                cin.ignore();
            getline(cin, type_name);

            if (type_name.empty() || check_string(type_name, '^'))
            {
                cout << "Invalid name. Cannot be empty or contain '^'. Try again.\n";
                continue;
            }
            else
            {
                break;
            }
        }
        string new_name = type_name;

        // Using Find_By_Name to check duplicates in the income array
        if (Find_By_Name(type_name, this->income, this->income_count, dummy_IS))
        {
            cout << "Source chosen successfully: " << type_name << endl;
            check_IS = false;
        }
        else
        {
            cout << "Income source does not exist, do you want to create a new incoce source?\n";
            cout << "Enter your choice (1/0): \n";
            cout << "1. Yes\n";
            cout << "2. No\n";
            // Clear buffer here also, Write me a function for clear buffer specifically
            cin >> choice;
            int new_IS_id;
            switch (choice)
            {
            case 1:
                // Auto add a income source here
                // name: new_name
                // ID: auto generate
                this->resize(); // Ensure capacity exists

                // --- AUTO ID GENERATION ---
                new_IS_id = Generate_ID(this->income, this->income_count);

                // --- SAVE TO ARRAY ---
                this->income[this->income_count] = new IncomeSource;
                this->income[this->income_count]->id = new_IS_id;
                this->income[this->income_count]->name = new_name;
                // Linking for later assigning
                dummy_IS = this->income[this->income_count];
                // Update size count
                this->income_count++;

                // --- OUTPUT FEEDBACK ---
                cout << "---------------------------------" << endl;
                cout << " New Income Source Added: " << new_name << endl;
                cout << " ID Assigned: " << new_IS_id << endl;
                cout << "---------------------------------" << endl;
                check_IS = false;
                break;

            case 0:
                cout << "Invalid Income Source\n";
                cout << "Press enter to go back...";
                cin.get();
                // User decline so we go back to ask them to type the name again
                break;
            default:
                cout << "Invalid Income Source\n";
                cout << "Press enter to go back...";
                cin.get();
                // User decline so we go back to ask them to type the name again
                break;
            }
        }
    }
    // --- INPUT LOOP TO GET AMOUNT---
    string s;
    long long validAmount = 0;
    bool check_W = true;
    while (true)
    {
        cout << "Enter your amount of transaction: ";
        cin >> s; // No spaces allowed in numbers, so cin is fine here

        // Use your existing helper
        if (isValidLongLong(s))
        {
            validAmount = stoll(s);
            break;
        }
    }

    // Wallet
    cin.ignore();
    while (true)
    {
        cout << "Enter Wallet Name: ";
        string wName;
        getline(cin, wName);
        Wallet *w = nullptr;
        if (Find_By_Name(wName, this->Wallet_List, this->wallet_count, w))
        {
            // ktra dư
            if (w->remain < trans->amount)
            {
                cout << "WARNING: Wallet balance (" << w->remain << ") is not enough! Continue? (1: Yes/ 0: No): ";
                int f;
                cin >> f;
                cin.ignore();
                if (f == 0)
                    continue;
            }

            // Find Wallet
            if (Find_By_Name(dummy.name, this->Wallet_List, this->wallet_count, dummy_W))
            {
                cout << "Wallet chosen successfully: " << dummy.name << endl;
                check_W = false;
            }
            else
            {
                cout << "Wallet does not exist, do you want to create a new Wallet?\n";
                cout << "Enter your choice (1/0): \n";
                cout << "1. Yes\n";
                cout << "2. No\n";
                // Clear buffer here also, Write me a function for clear buffer specifically
                int new_W_id;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    // Auto add a Wallet here
                    // name: new_name
                    // ID: auto generate
                    // Balance = 0;
                    this->resize(); // Ensure capacity exists

                    // --- AUTO ID GENERATION ---
                    new_W_id = Generate_ID(this->Wallet_List, this->wallet_count);

                    // 5. Save to List
                    Wallet_List[wallet_count] = new Wallet;
                    Wallet_List[wallet_count]->id = new_W_id; // Assign the auto-generated ID
                    Wallet_List[wallet_count]->name = dummy.name;
                    Wallet_List[wallet_count]->remain = 0;
                    dummy_W = Wallet_List[wallet_count];

                    wallet_count += 1;

                    cout << "---------------------------------" << endl;
                    cout << " New Wallet Created Successfully " << endl;
                    cout << " ID:      " << new_W_id << endl;
                    cout << " Name:    " << dummy.name << endl;
                    cout << " Balance: " << 0 << endl;
                    cout << "---------------------------------" << endl;

                case 0:
                    cout << "Invalid Wallet\n";
                    cout << "Press enter to go back...";
                    cin.get();
                    // User decline so we go back to ask them to type the name again
                    break;
                default:
                    cout << "Invalid Wallet\n";
                    cout << "Press enter to go back...";
                    cin.get();
                    // User decline so we go back to ask them to type the name again
                    break;
                }
            }
        }
    }

    // --- INPUT LOOP TO GET Description---
}
void User_Info::Add_Recur_Expense_Transaction()
{
}
void User_Info::Add_Recur_Income_Transaction()
{
}
