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

void User_Info::Add_Income_Transaction()
{

    if (inCount >= inCap)
        this->resize();

    Transaction_Income *trans = new Transaction_Income;

    string dateStr;
    do
    {
        cout << "Enter Date (dd/mm/yyyy): ";
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, dateStr);
        trans->date = InputDate(dateStr);
        if (trans->date.day == 0)
            cout << "Invalid Date!\n";
    } while (trans->date.day == 0);

    while (true)
    {
        cout << "Enter Source Name: ";
        string srcName;
        getline(cin, srcName);

        IncomeSource *foundSrc = nullptr;
        if (Find_By_Name(srcName, this->income, this->income_count, foundSrc))
        {
            trans->type = foundSrc;
            break;
        }
        else
        {
            cout << "Source not found! Create new? (1: Yes, 0: No): ";
            int choice;
            cin >> choice;
            cin.ignore();
            if (choice == 1)
            {
                this->Add_Income();

                trans->type = this->income[this->income_count - 1];
                break;
            }
        }
    }

    while (true)
    {
        cout << "Enter Amount: ";
        string s;
        cin >> s;
        if (isValidLongLong(s))
        {
            trans->amount = stoll(s);
            break;
        }
        cout << "Invalid amount!\n";
    }

    cin.ignore();
    while (true)
    {
        cout << "Enter Wallet Name: ";
        string wName;
        getline(cin, wName);

        Wallet *foundWallet = nullptr;
        if (Find_By_Name(wName, this->Wallet_List, this->wallet_count, foundWallet))
        {
            trans->wallet = foundWallet;
            break;
        }
        else
        {
            cout << "Wallet not found! Create new? (1: Yes, 0: No): ";
            int choice;
            cin >> choice;
            cin.ignore();
            if (choice == 1)
            {
                this->Add_Wallet();
                trans->wallet = this->Wallet_List[this->wallet_count - 1];
                break;
            }
        }
    }

    cout << "Enter Description: ";
    getline(cin, trans->description);

    trans->wallet->remain += trans->amount;
    trans->wallet->inCount++;

    this->incomes_transaction[this->inCount] = trans;
    this->inCount++;

    cout << "\n=== INCOME TRANSACTION ADDED SUCCESSFULLY ===\n";
}

void User_Info::Add_Expense_Transaction()
{
    if (expCount >= expCap)
        this->resize();
    Transaction_Expense *trans = new Transaction_Expense;

    // Date
    string dateStr;
    do
    {
        cout << "Enter Date (dd/mm/yyyy): ";
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, dateStr);
        trans->date = InputDate(dateStr);
    } while (trans->date.day == 0);

    // Category
    while (true)
    {
        cout << "Enter Category Name (e.g. Food): ";
        string catName;
        getline(cin, catName);
        ExpenseCategory *foundCat = nullptr;
        if (Find_By_Name(catName, this->expense, this->expense_count, foundCat))
        {
            trans->type = foundCat;
            break;
        }
        else
        {
            cout << "Category not found. Create new? (1: Yes / 0: Retry): ";
            int c;
            cin >> c;
            cin.ignore();
            if (c == 1)
            {
                Add_Expense();
                trans->type = this->expense[this->expense_count - 1];
                break;
            }
        }
    }

    // Amount
    while (true)
    {
        cout << "Enter Amount: ";
        string s;
        cin >> s;
        if (isValidLongLong(s))
        {
            trans->amount = stoll(s);
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
            trans->wallet = w;
            break;
        }
        else
        {
            cout << "Wallet not found.\n";
        }
    }

    cout << "Enter Description: ";
    getline(cin, trans->description);

    // Trừ ví
    trans->wallet->remain -= trans->amount;

    // lưu
    this->expenses_transaction[this->expCount] = trans;
    this->expCount++;
    cout << "\n=== EXPENSE TRANSACTION ADDED SUCCESSFULLY ===\n";
}

void User_Info::Add_Recur_Expense_Transaction()
{
}
void User_Info::Add_Recur_Income_Transaction()
{
}

// --- Bổ sung vào User_Info.cpp ---

void User_Info::Show_Wallet_List()
{
    cout << "\n==================== WALLET LIST ====================\n";
    cout << left << setw(5) << "ID"
         << left << setw(20) << "Wallet Name"
         << right << setw(15) << "Balance" << endl;
    cout << "-----------------------------------------------------\n";

    if (wallet_count == 0)
    {
        cout << "No wallets found.\n";
    }
    else
    {
        for (int i = 0; i < wallet_count; i++)
        {
            cout << left << setw(5) << Wallet_List[i]->id
                 << left << setw(20) << Wallet_List[i]->name
                 << right << setw(15) << Wallet_List[i]->remain << endl;
        }
    }
    cout << "=====================================================\n";
}

void User_Info::Show_Transaction_History()
{
    cout << "\n================ TRANSACTION HISTORY ================\n";

    // 1. Hiển thị Income
    if (inCount > 0)
    {
        cout << "\n--- [INCOME] ---\n";
        cout << left << setw(12) << "Date"
             << left << setw(15) << "Source"
             << left << setw(15) << "Wallet"
             << right << setw(12) << "Amount"
             << "   " << "Description" << endl;
        cout << "----------------------------------------------------------------\n";

        for (int i = 0; i < inCount; i++)
        {
            // In ngày tháng (giả sử OutputDate in ra không xuống dòng)
            OutputDate(incomes_transaction[i]->date);

            cout << "   " // Padding sau ngày
                 << left << setw(15) << (incomes_transaction[i]->type ? incomes_transaction[i]->type->name : "Unknown")
                 << left << setw(15) << (incomes_transaction[i]->wallet ? incomes_transaction[i]->wallet->name : "Unknown")
                 << right << setw(12) << incomes_transaction[i]->amount
                 << "   " << incomes_transaction[i]->description << endl;
        }
    }

    // 2. Hiển thị Expense
    if (expCount > 0)
    {
        cout << "\n--- [EXPENSE] ---\n";
        cout << left << setw(12) << "Date"
             << left << setw(15) << "Category"
             << left << setw(15) << "Wallet"
             << right << setw(12) << "Amount"
             << "   " << "Description" << endl;
        cout << "----------------------------------------------------------------\n";

        for (int i = 0; i < expCount; i++)
        {
            OutputDate(expenses_transaction[i]->date);

            cout << "   "
                 << left << setw(15) << (expenses_transaction[i]->type ? expenses_transaction[i]->type->name : "Unknown")
                 << left << setw(15) << (expenses_transaction[i]->wallet ? expenses_transaction[i]->wallet->name : "Unknown")
                 << right << setw(12) << expenses_transaction[i]->amount
                 << "   " << expenses_transaction[i]->description << endl;
        }
    }

    if (inCount == 0 && expCount == 0)
    {
        cout << "No transactions found.\n";
    }
    cout << "=====================================================\n";
}

void User_Info::Show_Recurring_Transaction_List()
{
    cout << "\n=== RECURRING TRANSACTIONS (Feature in progress) ===\n";
    // Tạm thời để trống hoặc in ra thông báo
    cout << "Income Recurring Count: " << recur_trans_income_count << endl;
    cout << "Expense Recurring Count: " << recur_trans_expense_count << endl;
}