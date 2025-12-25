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

void Show_Transaction_History();
void Show_Recurring_Transaction_List();
void User_Info::Add_Wallet()
{
    Wallet dummy;
    this->resize();

    // --- NAME INPUT LOOP ---
    while (true)
    {
        cout << "Enter your new wallet name: ";
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, dummy.name);

        if (dummy.name.empty() || check_string(dummy.name, '^'))
        {
            cout << "Invalid name (cannot be empty or contain '^').\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer(); // getline leaves buffer clean usually, but consistent with your template
            ClearLines(3);
            continue;
        }

        Wallet *save = nullptr;
        // Check for duplicate name
        if (Find_By_Name(dummy.name, this->Wallet_List, this->wallet_count, save))
        {
            cout << "Wallet name existed, please choose another name.\n";
            cout << "Press enter to retype...";
            cin.get();
            ClearLines(3);
        }
        else
        {
            break; // Name is valid and unique
        }
    }

    // --- BALANCE INPUT LOOP ---
    string s;
    long long validBalance = 0;
    while (true)
    {
        cout << "Enter your balance: ";
        cin >> s;

        if (isValidLongLong(s))
        {
            validBalance = stoll(s);
            break;
        }
        else
        {
            cout << "Invalid amount. Please enter a valid integer number.\n";
            cout << "Press enter to retype...";
            cin.ignore(); // cin >> leaves newline, consume it before cin.get()
            cin.get();
            ClearLines(3);
        }
    }

    // 4. GENERATE ID automatically
    int new_id = Generate_ID(this->Wallet_List, this->wallet_count);

    // 5. Save to List
    Wallet_List[wallet_count] = new Wallet;
    Wallet_List[wallet_count]->id = new_id;
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
    this->resize();
    string new_name;

    // --- INPUT LOOP ---
    while (true)
    {
        cout << "Enter new expense category name (e.g., Food): ";

        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, new_name);

        // Validation 1: Empty or Invalid Char
        if (new_name.empty() || check_string(new_name, '^'))
        {
            cout << "Invalid name. Cannot be empty or contain '^'.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
            continue;
        }

        // Validation 2: Duplicates
        ExpenseCategory *temp = nullptr;
        if (Find_By_Name(new_name, this->expense, this->expense_count, temp))
        {
            cout << "This category already exists! Please enter a different name.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
        else
        {
            break;
        }
    }

    // --- SAVE ---
    int new_id = Generate_ID(this->expense, this->expense_count);

    this->expense[this->expense_count] = new ExpenseCategory;
    this->expense[this->expense_count]->id = new_id;
    this->expense[this->expense_count]->name = new_name;

    this->expense_count++;

    cout << "---------------------------------" << endl;
    cout << " New Expense Category Added: " << new_name << endl;
    cout << " ID Assigned: " << new_id << endl;
    cout << "---------------------------------" << endl;
}

void User_Info::Add_Income()
{
    this->resize();
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
            cout << "Invalid name. Cannot be empty or contain '^'.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
            continue;
        }

        IncomeSource *temp = nullptr;
        if (Find_By_Name(new_name, this->income, this->income_count, temp))
        {
            cout << "This source already exists! Please enter a different name.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
        else
        {
            break;
        }
    }

    // --- SAVE ---
    int new_id = Generate_ID(this->income, this->income_count);

    this->income[this->income_count] = new IncomeSource;
    this->income[this->income_count]->id = new_id;
    this->income[this->income_count]->name = new_name;

    this->income_count++;

    cout << "---------------------------------" << endl;
    cout << " New Income Source Added: " << new_name << endl;
    cout << " ID Assigned: " << new_id << endl;
    cout << "---------------------------------" << endl;
}

void User_Info::Add_Expense_Transaction()
{
    this->resize(); // Ensure we have space before starting

    // --- STEP 1: DATE ---
    string dateStr;
    Date transDate;
    do
    {
        cout << "Enter Date of transaction (dd/mm/yyyy): ";
        // Optional: Clean buffer if coming from previous cin input
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, dateStr);
        transDate = InputDate(dateStr);

        if (transDate.day == 0)
        {
            cout << "Invalid date format! Please enter as format (e.g., 25/12/2023)...\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
    } while (transDate.day == 0);

    // --- STEP 2: EXPENSE CATEGORY ---
    string type_name;
    ExpenseCategory *dummy_EC = nullptr;
    bool check_EC = true;
    int choice;

    while (check_EC)
    {
        // Loop to get a valid name string
        while (true)
        {
            cout << "Enter your expense category name (e.g., Food): ";
            if (cin.peek() == '\n')
                cin.ignore();
            getline(cin, type_name);

            if (type_name.empty() || check_string(type_name, '^'))
            {
                cout << "Invalid name. Cannot be empty or contain '^'. Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(2);
                continue;
            }
            break;
        }

        // Check if exists
        if (Find_By_Name(type_name, this->expense, this->expense_count, dummy_EC))
        {
            cout << "Category chosen successfully: " << type_name << endl;
            check_EC = false;
        }
        else
        {
            cout << "Expense category does not exist. Do you want to create it?\n";
            cout << "1. Yes\n2. No\n0. Back to menu\n";

            do
            {
                cout << "Choice: ";
                cin >> choice;
                Clear_Buffer();

                switch (choice)
                {
                case 1:
                {
                    // Auto-create Category
                    this->resize();
                    int new_EC_id = Generate_ID(this->expense, this->expense_count);

                    this->expense[this->expense_count] = new ExpenseCategory;
                    this->expense[this->expense_count]->id = new_EC_id;
                    this->expense[this->expense_count]->name = type_name;

                    // Link immediately
                    dummy_EC = this->expense[this->expense_count];
                    this->expense_count++;

                    cout << "---------------------------------" << endl;
                    cout << " New Expense Category Added: " << type_name << endl;
                    cout << " ID Assigned: " << new_EC_id << endl;
                    cout << "---------------------------------" << endl;
                    check_EC = false;
                    choice = 0;
                    break;
                }
                case 2:
                    cout << "Please choose an existing category or create a new one.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(8);
                    choice = 0;
                    break;
                case 0:
                    return; // Exit function
                default:
                    cout << "Invalid choice.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(3);
                    break;
                }

            } while (choice != 0);
        }
    }

    // --- STEP 3: AMOUNT ---
    string s;
    long long validAmount = 0;
    while (true)
    {
        cout << "Enter expense amount: ";
        cin >> s;

        if (isValidLongLong(s))
        {
            validAmount = stoll(s);
            if (validAmount < 0)
            {
                cout << "Amount cannot be negative. Enter a positive value (it will be subtracted).\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(3);
                continue;
            }
            break;
        }
        else
        {
            cout << "Invalid amount. Please enter a valid integer.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
    }

    // --- STEP 4: WALLET ---
    Wallet dummy;
    Wallet *dummy_W = nullptr;
    bool check_W = true;

    while (check_W)
    {
        while (true)
        {
            cout << "Enter wallet name to pay from: ";
            if (cin.peek() == '\n')
                cin.ignore();
            getline(cin, dummy.name);

            if (dummy.name.empty() || check_string(dummy.name, '^'))
            {
                cout << "Invalid name. Try again.\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(3);
                continue;
            }
            break;
        }

        // Find Wallet
        if (Find_By_Name(dummy.name, this->Wallet_List, this->wallet_count, dummy_W))
        {
            // Optional: Warning if balance will go negative
            if (dummy_W->remain < validAmount)
            {
                cout << "Warning: This expense will make the wallet balance negative.\n";
            }
            cout << "Wallet chosen: " << dummy.name << endl;
            check_W = false;
        }
        else
        {
            cout << "Wallet not found. Create new?\n1. Yes\n2. No\n0. Cancel\n";
            do
            {
                cout << "Choice: ";
                cin >> choice;
                Clear_Buffer();

                switch (choice)
                {
                case 1:
                {
                    this->resize();
                    int new_W_id = Generate_ID(this->Wallet_List, this->wallet_count);

                    Wallet_List[wallet_count] = new Wallet;
                    Wallet_List[wallet_count]->id = new_W_id;
                    Wallet_List[wallet_count]->name = dummy.name;
                    Wallet_List[wallet_count]->remain = 0;

                    dummy_W = Wallet_List[wallet_count];
                    wallet_count++;

                    cout << "---------------------------------" << endl;
                    cout << " New Wallet Created Successfully " << endl;
                    cout << " ID:      " << new_W_id << endl;
                    cout << " Name:    " << dummy.name << endl;
                    cout << " Balance: " << 0 << endl;
                    cout << "---------------------------------" << endl;
                    check_W = false;
                    choice = 0;
                    break;
                }
                case 2:
                    cout << "Please enter a exist wallet name\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(8);
                    break;
                case 0:
                    return;
                default:
                    cout << "Invalid choice.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(3);
                    break;
                }
            } while (choice != 0);
        }
    }

    // --- STEP 5: DESCRIPTION ---
    string Des_Input;
    cout << "Enter description: ";
    if (cin.peek() == '\n')
        cin.ignore();
    getline(cin, Des_Input);

    // --- STEP 6: SAVE & UPDATE BALANCE ---
    this->resize(); // Final check

    expenses_transaction[expCount] = new Transaction_Expense;
    expenses_transaction[expCount]->date = transDate;
    expenses_transaction[expCount]->type = dummy_EC;
    expenses_transaction[expCount]->wallet = dummy_W;
    expenses_transaction[expCount]->amount = validAmount;
    expenses_transaction[expCount]->description = Des_Input;

    // Trừ tiền trong ví
    dummy_W->remain -= validAmount;
    dummy_W->Wallet_resize();
    dummy_W->expenses[dummy_W->expCount] = expenses_transaction[expCount];
    dummy_W->expCount += 1;
    cout << "Expense Transaction Added Successfully!\n";
    cout << "New Balance of " << dummy_W->name << ": " << dummy_W->remain << endl;
    expCount++;
}
void User_Info::Add_Income_Transaction()
{
    string dateStr;
    // DATE
    Date transDate;
    // --- INPUT LOOP TO GET DATE---
    do
    {
        if (cin.peek() == '\n')
            cin.ignore();
        cout << "Enter Date of transaction (dd/mm/yyyy): ";
        getline(cin, dateStr);
        transDate = InputDate(dateStr);

        if (transDate.day == 0)
        {
            cout << "Invalid date format or logic! (e.g., 25/12/2023).\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
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
                cout << "Invalid name. Cannot be empty or contain '^'.\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(3);
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
            cout << "0. Back to menu\n";
            do
            {
                cout << "Enter your choice: ";
                cin >> choice;
                Clear_Buffer(); // Clear newline after cin >> choice

                int new_IS_id;
                switch (choice)
                {
                case 1:
                    this->resize();
                    new_IS_id = Generate_ID(this->income, this->income_count);

                    this->income[this->income_count] = new IncomeSource;
                    this->income[this->income_count]->id = new_IS_id;
                    this->income[this->income_count]->name = new_name;
                    dummy_IS = this->income[this->income_count];
                    this->income_count++;

                    cout << "---------------------------------" << endl;
                    cout << " New Income Source Added: " << new_name << endl;
                    cout << " ID Assigned: " << new_IS_id << endl;
                    cout << "---------------------------------" << endl;
                    check_IS = false;
                    choice = 0; // Break do-while
                    break;

                case 2:
                    cout << "Please type the name again.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(8); // Clear menu and previous inputs
                    choice = 0;    // Break do-while to loop back to name input
                    break;

                case 0:
                    return;

                default:
                    cout << "Invalid choice.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(3);
                    break;
                }
            } while (choice != 0 && check_IS); // Loop if invalid choice
        }
    }
    // --- INPUT LOOP TO GET AMOUNT---
    string s;
    long long validAmount = 0;
    while (true)
    {
        cout << "Enter your amount of transaction: ";
        cin >> s; // No spaces allowed in numbers, so cin is fine here

        // Use your existing helper
        if (isValidLongLong(s))
        {
            cout << "Your amount is valid!" << endl;
            validAmount = stoll(s);
            break;
        }
        else
        {
            cout << "Invalid amount. Please enter a valid integer number.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
    }
    // --- INPUT LOOP TO GET WALLET---
    // dummy for getting input
    Wallet dummy;
    bool check_W = true;
    // Dummy pointer for later linking
    Wallet *dummy_W = nullptr;
    while (check_W)
    {
        while (true)
        {
            cout << "Enter your wallet name: ";
            // Show_Wallet();
            // Draw all Wallet for user to choose
            if (cin.peek() == '\n')
                cin.ignore();
            getline(cin, dummy.name);

            if (dummy.name.empty() || check_string(dummy.name, '^'))
            {
                cout << "Invalid name (cannot be empty or contain '^').\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(3);
                continue;
            }

            // Find Wallet
            if (Find_By_Name(dummy.name, this->Wallet_List, this->wallet_count, dummy_W))
            {
                cout << "Wallet chosen successfully: " << dummy.name << endl;
                check_W = false;
                break;
            }
            else
            {
                cout << "Wallet does not exist, do you want to create a new Wallet?\n";
                cout << "1. Yes\n";
                cout << "2. No\n";
                cout << "0. Back to menu\n";

                int new_W_id;

                do
                {
                    cout << "Enter your choice: ";
                    cin >> choice;
                    Clear_Buffer();

                    switch (choice)
                    {
                    case 1:
                        this->resize();
                        new_W_id = Generate_ID(this->Wallet_List, this->wallet_count);

                        Wallet_List[wallet_count] = new Wallet;
                        Wallet_List[wallet_count]->id = new_W_id;
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
                        check_W = false;
                        choice = 0;
                        break;

                    case 2:
                        cout << "Please type the name again.\n";
                        cout << "Press enter to retype...";
                        cin.get();
                        Clear_Buffer();
                        ClearLines(8);
                        choice = 0; // Break do-while, go back to name loop
                        break;

                    case 0:
                        return;

                    default:
                        cout << "Invalid choice.\n";
                        cout << "Press enter to retype...";
                        cin.get();
                        Clear_Buffer();
                        ClearLines(3);
                        break;
                    }
                } while (choice != 0 && check_W);
                if (!check_W)
                    break; // Break name loop if wallet created
            }
        }
    }

    // --- INPUT LOOP TO GET Description---
    string Des_Input;
    cout << "Enter your description, press enter to finish: ";
    getline(cin, Des_Input);

    resize();
    incomes_transaction[inCount] = new Transaction_Income;
    incomes_transaction[inCount]->date = transDate;
    incomes_transaction[inCount]->type = dummy_IS;
    incomes_transaction[inCount]->wallet = dummy_W;
    incomes_transaction[inCount]->amount = validAmount;
    incomes_transaction[inCount]->wallet->remain += validAmount;
    incomes_transaction[inCount]->description = Des_Input;

    // Wallet Linking back
    incomes_transaction[inCount]->wallet->Wallet_resize();
    incomes_transaction[inCount]->wallet->incomes[incomes_transaction[inCount]->wallet->inCount] = incomes_transaction[inCount];
    incomes_transaction[inCount]->wallet->inCount += 1;
    cout << "New Income Transaction Added\n";
    cout << "New Balance of " << dummy_W->name << ": " << dummy_W->remain << endl;
    // prinout all the informatuin one more time for the user to check
    inCount += 1;
}
void User_Info::Add_Recur_Expense_Transaction()
{
    this->resize();

    // --- STEP 1: START DATE ---
    string dateStr;
    Date startDate;
    do
    {
        cout << "Enter Start Date (dd/mm/yyyy): ";
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, dateStr);
        startDate = InputDate(dateStr);

        if (startDate.day == 0)
        {
            cout << "Invalid date format! Please try again.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
    } while (startDate.day == 0);

    // --- STEP 2: END DATE ---
    Date endDate;
    while (true)
    {
        cout << "Enter end date 31/12/3000 to make your transaction recur indefinitely\n";
        cout << "Enter End Date (dd/mm/yyyy): ";
        getline(cin, dateStr);
        endDate = InputDate(dateStr);

        if (endDate.day == 0)
        {
            cout << "Invalid date format! Please try again.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(4);
            continue;
        }

        if (!Date_Less_Or_Equal(startDate, endDate))
        {
            cout << "Error: End Date cannot be before Start Date.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(4);
        }
        else
        {
            break;
        }
    }

    // --- STEP 3: EXPENSE CATEGORY ---
    string type_name;
    ExpenseCategory *dummy_EC = nullptr;
    bool check_EC = true;
    int choice;

    while (check_EC)
    {
        while (true)
        {
            cout << "Enter expense category name (e.g., Rent): ";
            getline(cin, type_name);

            if (type_name.empty() || check_string(type_name, '^'))
            {
                cout << "Invalid name. Try again.\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(3);
                continue;
            }
            break;
        }

        if (Find_By_Name(type_name, this->expense, this->expense_count, dummy_EC))
        {
            cout << "Category chosen: " << type_name << endl;
            check_EC = false;
        }
        else
        {
            cout << "Category does not exist. Create new?\n1. Yes\n2. No\n0. Cancel\n";

            do
            {
                cout << "Choice: ";
                cin >> choice;
                Clear_Buffer();

                switch (choice)
                {
                case 1:
                {
                    this->resize();
                    int new_EC_id = Generate_ID(this->expense, this->expense_count);

                    this->expense[this->expense_count] = new ExpenseCategory;
                    this->expense[this->expense_count]->id = new_EC_id;
                    this->expense[this->expense_count]->name = type_name;

                    dummy_EC = this->expense[this->expense_count];
                    this->expense_count++;
                    ClearLines(5);
                    cout << "New Category Created: " << type_name << endl;
                    check_EC = false;
                    choice = 0;
                    break;
                }
                case 2:
                    cout << "Please type the name again.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(8);
                    choice = 0;
                    break;
                case 0:
                    return;
                default:
                    cout << "Invalid choice.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(3);
                    break;
                }
            } while (choice != 0 && check_EC);
        }
    }

    // --- STEP 4: AMOUNT ---
    string s;
    long long validAmount = 0;
    while (true)
    {
        cout << "Enter recurring amount: ";
        cin >> s;

        if (isValidLongLong(s))
        {
            validAmount = stoll(s);
            if (validAmount < 0)
            {
                cout << "Amount must be positive.\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(3);
                continue;
            }
            break;
        }
        cout << "Invalid integer amount.\n";
        cout << "Press enter to retype...";
        cin.get();
        Clear_Buffer();
        ClearLines(3);
    }

    // --- STEP 5: WALLET ---
    Wallet dummy;
    Wallet *dummy_W = nullptr;
    bool check_W = true;

    while (check_W)
    {
        while (true)
        {
            cout << "Enter wallet name: ";
            if (cin.peek() == '\n')
                cin.ignore();
            getline(cin, dummy.name);

            if (dummy.name.empty() || check_string(dummy.name, '^'))
            {
                cout << "Invalid name.\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(3);
                continue;
            }
            break;
        }

        if (Find_By_Name(dummy.name, this->Wallet_List, this->wallet_count, dummy_W))
        {
            cout << "Wallet chosen: " << dummy.name << endl;
            check_W = false;
        }
        else
        {
            cout << "Wallet not found. Create new?\n1. Yes\n2. No\n0. Cancel\n";

            do
            {
                cout << "Choice: ";
                cin >> choice;
                Clear_Buffer();

                switch (choice)
                {
                case 1:
                {
                    this->resize();
                    int new_W_id = Generate_ID(this->Wallet_List, this->wallet_count);

                    Wallet_List[wallet_count] = new Wallet;
                    Wallet_List[wallet_count]->id = new_W_id;
                    Wallet_List[wallet_count]->name = dummy.name;
                    Wallet_List[wallet_count]->remain = 0;

                    dummy_W = Wallet_List[wallet_count];
                    wallet_count++;

                    cout << "New Wallet Created: " << dummy.name << endl;
                    check_W = false;
                    choice = 0;
                    break;
                }
                case 2:
                    cout << "Please type the name again.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(8);
                    choice = 0;
                    break;
                case 0:
                    return;
                default:
                    cout << "Invalid choice.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(3);
                    break;
                }
            } while (choice != 0 && check_W);
        }
    }

    // --- STEP 6: DESCRIPTION ---
    string Des_Input;
    cout << "Enter description: ";
    if (cin.peek() == '\n')
        cin.ignore();
    getline(cin, Des_Input);

    // --- STEP 7: SAVE ---
    this->resize();
    int new_RTE_id = Generate_ID(Recurring_Transaction_Expense_List, recur_trans_expense_count);
    Recurring_Transaction_Expense_List[recur_trans_expense_count] = new Recurring_Transaction_Expense;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->id = new_RTE_id;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->start = startDate;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->end = endDate;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->type = dummy_EC;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->wallet = dummy_W;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->amount = validAmount;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->description = Des_Input;

    recur_trans_expense_count++;

    cout << "---------------------------------------" << endl;
    cout << " Recurring Expense Scheduled! " << endl;
    cout << "---------------------------------------" << endl;
    cout << "Press enter to retype...";
    cin.get();
    Clear_Buffer();
}

void User_Info::Add_Recur_Income_Transaction()
{
    this->resize();

    // --- STEP 1: START DATE ---
    string dateStr;
    Date startDate;
    do
    {
        cout << "Enter Start Date (dd/mm/yyyy): ";
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, dateStr);
        startDate = InputDate(dateStr);

        if (startDate.day == 0)
        {
            cout << "Invalid date format! Please try again.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
    } while (startDate.day == 0);

    // --- STEP 2: END DATE ---
    Date endDate;
    while (true)
        {
            cout << "Enter end date 31/12/3000 to make your transaction recur indefinitely\n";
            cout << "Enter End Date (dd/mm/yyyy): ";
            getline(cin, dateStr);
            endDate = InputDate(dateStr);

            if (endDate.day == 0)
            {
                cout << "Invalid date format! Please try again.\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(4);
                continue;
            }

            if (!Date_Less_Or_Equal(startDate, endDate))
            {
                cout << "Error: End Date cannot be before Start Date.\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(4);
            }
            else
            {
                break;
            }
        }

    // --- STEP 3: INCOME SOURCE ---
    string type_name;
    IncomeSource *dummy_IS = nullptr;
    bool check_IS = true;
    int choice;

    while (check_IS)
    {
        while (true)
        {
            cout << "Enter income source name (e.g., Salary): ";
            getline(cin, type_name);

            if (type_name.empty() || check_string(type_name, '^'))
            {
                cout << "Invalid name. Try again.\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(3);
                continue;
            }
            break;
        }

        if (Find_By_Name(type_name, this->income, this->income_count, dummy_IS))
        {
            cout << "Source chosen: " << type_name << endl;
            check_IS = false;
        }
        else
        {
            cout << "Source does not exist. Create new?\n1. Yes\n2. No\n0. Cancel\n";

            do
            {
                cout << "Choice: ";
                cin >> choice;
                Clear_Buffer();

                switch (choice)
                {
                case 1:
                {
                    this->resize();
                    int new_IS_id = Generate_ID(this->income, this->income_count);

                    this->income[this->income_count] = new IncomeSource;
                    this->income[this->income_count]->id = new_IS_id;
                    this->income[this->income_count]->name = type_name;

                    dummy_IS = this->income[this->income_count];
                    this->income_count++;

                    cout << "New Income Source Created: " << type_name << endl;
                    check_IS = false;
                    choice = 0;
                    break;
                }
                case 2:
                    cout << "Please type the name again.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(8);
                    choice = 0;
                    break;
                case 0:
                    return;
                default:
                    cout << "Invalid choice.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(3);
                    break;
                }
            } while (choice != 0 && check_IS);
        }
    }

    // --- STEP 4: AMOUNT ---
    string s;
    long long validAmount = 0;
    while (true)
    {
        cout << "Enter recurring amount: ";
        cin >> s;

        if (isValidLongLong(s))
        {
            validAmount = stoll(s);
            if (validAmount < 0)
            {
                cout << "Amount must be positive.\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(3);
                continue;
            }
            break;
        }
        cout << "Invalid integer amount.\n";
        cout << "Press enter to retype...";
        cin.get();
        Clear_Buffer();
        ClearLines(3);
    }

    // --- STEP 5: WALLET ---
    Wallet dummy;
    Wallet *dummy_W = nullptr;
    bool check_W = true;

    while (check_W)
    {
        while (true)
        {
            cout << "Enter target wallet name: ";
            if (cin.peek() == '\n')
                cin.ignore();
            getline(cin, dummy.name);

            if (dummy.name.empty() || check_string(dummy.name, '^'))
            {
                cout << "Invalid name.\n";
                cout << "Press enter to retype...";
                cin.get();
                Clear_Buffer();
                ClearLines(3);
                continue;
            }
            break;
        }

        if (Find_By_Name(dummy.name, this->Wallet_List, this->wallet_count, dummy_W))
        {
            cout << "Wallet chosen: " << dummy.name << endl;
            check_W = false;
        }
        else
        {
            cout << "Wallet not found. Create new?\n1. Yes\n2. No\n0. Cancel\n";

            do
            {
                cout << "Choice: ";
                cin >> choice;
                Clear_Buffer();

                switch (choice)
                {
                case 1:
                {
                    this->resize();
                    int new_W_id = Generate_ID(this->Wallet_List, this->wallet_count);

                    Wallet_List[wallet_count] = new Wallet;
                    Wallet_List[wallet_count]->id = new_W_id;
                    Wallet_List[wallet_count]->name = dummy.name;
                    Wallet_List[wallet_count]->remain = 0;

                    dummy_W = Wallet_List[wallet_count];
                    wallet_count++;

                    cout << "New Wallet Created: " << dummy.name << endl;
                    check_W = false;
                    choice = 0;
                    break;
                }
                case 2:
                    cout << "Please type the name again.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(8);
                    choice = 0;
                    break;
                case 0:
                    return;
                default:
                    cout << "Invalid choice.\n";
                    cout << "Press enter to retype...";
                    cin.get();
                    Clear_Buffer();
                    ClearLines(3);
                    break;
                }
            } while (choice != 0 && check_W);
        }
    }

    // --- STEP 6: DESCRIPTION ---
    string Des_Input;
    cout << "Enter description: ";
    if (cin.peek() == '\n')
        cin.ignore();
    getline(cin, Des_Input);

    // --- STEP 7: SAVE ---
    this->resize();
    int new_RTI_id = Generate_ID(Recurring_Transaction_Income_List, recur_trans_income_count);
    Recurring_Transaction_Income_List[recur_trans_income_count] = new Recurring_Transaction_Income;
    Recurring_Transaction_Income_List[recur_trans_income_count]->id = new_RTI_id;
    Recurring_Transaction_Income_List[recur_trans_income_count]->start = startDate;
    Recurring_Transaction_Income_List[recur_trans_income_count]->end = endDate;
    Recurring_Transaction_Income_List[recur_trans_income_count]->type = dummy_IS;
    Recurring_Transaction_Income_List[recur_trans_income_count]->wallet = dummy_W;
    Recurring_Transaction_Income_List[recur_trans_income_count]->amount = validAmount;
    Recurring_Transaction_Income_List[recur_trans_income_count]->description = Des_Input;

    recur_trans_income_count++;

    cout << "---------------------------------------" << endl;
    cout << " Recurring Income Scheduled! " << endl;
    cout << "---------------------------------------" << endl;
}
// --- Bổ sung vào User_Info.cpp ---
// --- Helper to ensure uniform date spacing (10 chars + 2 padding) ---
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
    while (Date_Less_Or_Equal(iterator_date, current_date))
    {
        // Stop if we have passed the recurring end date (if one is set)
        if (p->end.day != 0)
        { // Assuming day=0 means "no end date"
            if (!Date_Less_Or_Equal(iterator_date, p->end))
                break;
        }

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
            expenses_transaction[expCount]->description = "(Auto-Generated)" + p->description;

            // 5. UPDATE WALLET BALANCE
            p->wallet->remain -= p->amount;

            // Link transaction to Wallet's internal list
            p->wallet->Wallet_resize();
            p->wallet->expenses[p->wallet->expCount] = expenses_transaction[expCount];
            p->wallet->expCount++;

            // Increment User_Info global count
            this->expCount++;
            has_changes = true;

            cout << " [Auto] Generated recurring expense for: "
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
    while (Date_Less_Or_Equal(iterator_date, current_date))
    {
        // Stop if we have passed the recurring end date (if one is set)
        if (p->end.day != 0)
        {
            if (!Date_Less_Or_Equal(iterator_date, p->end))
                break;
        }

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

            cout << " [Auto] Generated recurring income for: "
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
bool User_Info::IsDateInRange(Date target, Date start, Date end)
{

    bool start_ok = false;
    if (target.year > start.year)
        start_ok = true;
    else if (target.year == start.year && target.month > start.month)
        start_ok = true;
    else if (target.year == start.year && target.month == start.month && target.day >= start.day)
        start_ok = true;

    //

    bool end_ok = false;
    if (target.year < end.year)
        end_ok = true;
    else if (target.year == end.year && target.month < end.month)
        end_ok = true;
    else if (target.year == end.year && target.month == end.month && target.day <= end.day)
        end_ok = true;

    return start_ok && end_ok;
}

// time based
void User_Info::Stats_TimeRange()
{
    cout << "\n=== STATISTICS BY TIME RANGE ===\n";

    // Nhập ngày
    string sDate;
    Date dStart, dEnd;

    do
    {
        if (cin.peek() == '\n')
            cin.ignore();
        cout << "Enter Start Date (dd/mm/yyyy): ";
        getline(cin, sDate);
        dStart = InputDate(sDate);
    } while (dStart.day == 0);

    do
    {
        cout << "Enter End Date (dd/mm/yyyy): ";
        getline(cin, sDate);
        dEnd = InputDate(sDate);
    } while (dEnd.day == 0);

    long long totalIncome = 0;
    long long totalExpense = 0;

    // Tính tổng Income
    for (int i = 0; i < inCount; i++)
    {
        if (IsDateInRange(incomes_transaction[i]->date, dStart, dEnd))
        {
            totalIncome += incomes_transaction[i]->amount;
        }
    }

    // Tính tổng Expense
    for (int i = 0; i < expCount; i++)
    {
        if (IsDateInRange(expenses_transaction[i]->date, dStart, dEnd))
        {
            totalExpense += expenses_transaction[i]->amount;
        }
    }

    // Hiển thị
    cout << "\n--------------------------------------------------\n";
    cout << " Period: ";
    OutputDate(dStart);
    cout << " - ";
    OutputDate(dEnd);
    cout << endl;
    cout << "--------------------------------------------------\n";
    cout << left << setw(30) << " Total Income:" << right << setw(15) << totalIncome << endl;
    cout << left << setw(30) << " Total Expense:" << right << setw(15) << totalExpense << endl;
    cout << "--------------------------------------------------\n";
    cout << left << setw(30) << " NET BALANCE:" << right << setw(15) << (totalIncome - totalExpense) << endl;
    cout << "--------------------------------------------------\n";
    cout << "Press Enter to continue...";
    cin.get();
}

// wallet-based
void User_Info::Stats_Wallet_TimeRange()
{
    cout << "\n=== STATISTICS BY WALLET & TIME ===\n";

    // Chọn ví
    Wallet *targetWallet = nullptr;
    string wName;
    while (true)
    {
        cout << "Enter Wallet Name to filter (e.g., Cash): ";
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, wName);
        targetWallet = Choose_Wallet(wName);
        if (targetWallet != nullptr)
            break;
        cout << " [!] Wallet not found. Try again.\n";
    }

    // Nhập ngày
    string sDate;
    Date dStart, dEnd;
    cout << "Enter Start Date (dd/mm/yyyy): ";
    getline(cin, sDate);
    dStart = InputDate(sDate);
    cout << "Enter End Date (dd/mm/yyyy): ";
    getline(cin, sDate);
    dEnd = InputDate(sDate);

    if (dStart.day == 0 || dEnd.day == 0)
    {
        cout << "Invalid date input.\n";
        return;
    }

    long long wIncome = 0;
    long long wExpense = 0;

    // calculate in
    for (int i = 0; i < inCount; i++)
    {
        if (incomes_transaction[i]->wallet->id == targetWallet->id &&
            IsDateInRange(incomes_transaction[i]->date, dStart, dEnd))
        {
            wIncome += incomes_transaction[i]->amount;
        }
    }

    // calculate exp
    for (int i = 0; i < expCount; i++)
    {
        if (expenses_transaction[i]->wallet->id == targetWallet->id &&
            IsDateInRange(expenses_transaction[i]->date, dStart, dEnd))
        {
            wExpense += expenses_transaction[i]->amount;
        }
    }

    cout << "\n--- Wallet: " << targetWallet->name << " ---\n";
    cout << " + Income:  " << wIncome << endl;
    cout << " - Expense: " << wExpense << endl;
    cout << " = Net:     " << (wIncome - wExpense) << endl;
    cout << "----------------------------------\n";
    cout << "Press Enter to continue...";
    cin.get();
}

// Annual

void User_Info::Stats_Annual_Overview()
{
    cout << "\n=== ANNUAL INCOME/EXPENSE OVERVIEW ===\n";
    int startYear, endYear;
    cout << "Enter Start Year (e.g., 2023): ";
    cin >> startYear;
    cout << "Enter End Year (e.g., 2025): ";
    cin >> endYear;
    Clear_Buffer();

    if (startYear > endYear)
    {
        int temp = startYear;
        startYear = endYear;
        endYear = temp;
    }

    cout << "\n";
    cout << left << setw(10) << "YEAR"
         << right << setw(20) << "TOTAL INCOME"
         << right << setw(20) << "TOTAL EXPENSE"
         << right << setw(20) << "NET BALANCE" << endl;
    cout << string(70, '-') << endl;

    for (int y = startYear; y <= endYear; y++)
    {
        long long yInc = 0;
        long long yExp = 0;

        // sum in of year
        for (int i = 0; i < inCount; i++)
        {
            if (incomes_transaction[i]->date.year == y)
                yInc += incomes_transaction[i]->amount;
        }

        // exp of year y
        for (int i = 0; i < expCount; i++)
        {
            if (expenses_transaction[i]->date.year == y)
                yExp += expenses_transaction[i]->amount;
        }

        cout << left << setw(10) << y
             << right << setw(20) << yInc
             << right << setw(20) << yExp
             << right << setw(20) << (yInc - yExp) << endl;
    }
    cout << string(70, '-') << endl;
    cout << "Press Enter to continue...";
    cin.get();
}

// Breakdown

void User_Info::Stats_Annual_Breakdown()
{
    cout << "\n=== ANNUAL BREAKDOWN ===\n";
    int year;
    cout << "Enter Year to analyze: ";
    cin >> year;
    Clear_Buffer();

    cout << "\n [INCOME BREAKDOWN - " << year << "]\n";
    cout << left << setw(30) << "Source Name" << right << setw(20) << "Amount" << endl;
    cout << string(50, '-') << endl;

    long long grandTotalInc = 0;

    // duyệt tron mastẻrdata các loại in
    for (int i = 0; i < income_count; i++)
    {
        long long catTotal = 0;
        // duyệt trans
        for (int k = 0; k < inCount; k++)
        {
            if (incomes_transaction[k]->date.year == year &&
                incomes_transaction[k]->type->id == income[i]->id)
            {
                catTotal += incomes_transaction[k]->amount;
            }
        }

        if (catTotal > 0)
        { // hiện những nguồn có tiền
            cout << left << setw(30) << income[i]->name << right << setw(20) << catTotal << endl;
            grandTotalInc += catTotal;
        }
    }
    cout << string(50, '-') << endl;
    cout << left << setw(30) << "TOTAL:" << right << setw(20) << grandTotalInc << endl;

    cout << "\n [EXPENSE BREAKDOWN - " << year << "]\n";
    cout << left << setw(30) << "Category Name" << right << setw(20) << "Amount" << endl;
    cout << string(50, '-') << endl;

    long long grandTotalExp = 0;

    // duyệt exp
    for (int i = 0; i < expense_count; i++)
    {
        long long catTotal = 0;
        // duyệt trans
        for (int k = 0; k < expCount; k++)
        {
            if (expenses_transaction[k]->date.year == year &&
                expenses_transaction[k]->type->id == expense[i]->id)
            {
                catTotal += expenses_transaction[k]->amount;
            }
        }

        if (catTotal > 0)
        {
            cout << left << setw(30) << expense[i]->name << right << setw(20) << catTotal << endl;
            grandTotalExp += catTotal;
        }
    }
    cout << string(50, '-') << endl;
    cout << left << setw(30) << "TOTAL:" << right << setw(20) << grandTotalExp << endl;

    cout << "\nPress Enter to continue...";
    cin.get();
}

// MENU
void User_Info::Draw_Statistics_Menu()
{
    while (true)
    {
        system("cls");
        cout << "=========================================\n";
        cout << "       STATISTICS & REPORTS              \n";
        cout << "=========================================\n";
        cout << "1. Time-based Statistics (Range)\n";
        cout << "2. Wallet-based Statistics (Range)\n";
        cout << "3. Annual Overview (Compare Years)\n";
        cout << "4. Annual Breakdown (Source/Category)\n";
        cout << "0. Back to Main Menu\n";
        cout << "-----------------------------------------\n";
        cout << "Select option: ";

        int choice;
        cin >> choice;
        Clear_Buffer();

        switch (choice)
        {
        case 1:
            Stats_TimeRange();
            break;
        case 2:
            Stats_Wallet_TimeRange();
            break;
        case 3:
            Stats_Annual_Overview();
            break;
        case 4:
            Stats_Annual_Breakdown();
            break;
        case 0:
            return;
        default:
            cout << "Invalid option!\n";
            cin.get();
            break;
        }
    }
}

//
//
//
//
//
//
//
//
// check ví và data có nên xóa
bool User_Info::Is_Wallet_In_Use(int id)
{
    // Check in
    for (int i = 0; i < inCount; i++)
    {
        if (incomes_transaction[i]->wallet->id == id)
            return true;
    }
    // Check iexp
    for (int i = 0; i < expCount; i++)
    {
        if (expenses_transaction[i]->wallet->id == id)
            return true;
    }
    // Ch có recurr
    //
    //
    // this is for recur

    return false;
}

bool User_Info::Is_Category_In_Use(int id)
{
    // Check exp
    for (int i = 0; i < expCount; i++)
    {
        if (expenses_transaction[i]->type->id == id)
            return true;
    }
    // check recurr
    for (int i = 0; i < recur_trans_expense_count; i++)
    {
        if (Recurring_Transaction_Expense_List[i]->type->id == id)
            return true;
    }
    return false;
}

bool User_Info::Is_Source_In_Use(int id)
{
    // Check in
    for (int i = 0; i < inCount; i++)
    {
        if (incomes_transaction[i]->type->id == id)
            return true;
    }
    // Check recur
    for (int i = 0; i < recur_trans_income_count; i++)
    {
        if (Recurring_Transaction_Income_List[i]->type->id == id)
            return true;
    }
    return false;
}
//
//
//
//
//
//
// Add, Edit, Delete
//
//
//
//
//
void User_Info::Edit_Wallet()
{
    Show_Wallet_List();
    int id;
    cout << "Enter Wallet ID to Edit: ";
    if (!(cin >> id))
    {
        Clear_Buffer();
        return;
    }
    Clear_Buffer();

    // Tìm ví
    Wallet *target = nullptr;
    if (!Find_By_ID(id, Wallet_List, wallet_count, target) || target == nullptr)
    {
        cout << " [Error] Wallet ID not found.\n";
        system("pause");
        return;
    }

    cout << "Current Name: " << target->name << endl;
    cout << "Enter New Name: ";
    string newName;
    getline(cin, newName);

    if (newName.empty() || check_string(newName, '^'))
    {
        cout << " [Error] Invalid name.\n";
        return;
    }

    // Check trùng tên
    Wallet *dupCheck = nullptr;
    if (Find_By_Name(newName, Wallet_List, wallet_count, dupCheck))
    {
        cout << " [Error] Name already exists!\n";
        return;
    }

    target->name = newName;
    cout << " [Success] Wallet updated.\n";
    system("pause");
}

void User_Info::Delete_Wallet()
{
    Show_Wallet_List();
    int id;
    string input;
    bool check=true;
    Wallet *dummy;
    while(check)
    {
    cout << "Enter Wallet ID to Delete: ";
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
        if(id==0 || !Find_By_ID(id, Wallet_List, wallet_count, dummy))
        {
            cout << "Error: Please Input an valid ID.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
        else
        check=false;
    }
    }
    Clear_Buffer();

    // Tìm vị trí trong mảng
    int index = -1;
    for (int i = 0; i < wallet_count; i++)
    {
        if (Wallet_List[i]->id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << " [Error] Wallet ID not found.\n";
        system("pause");
        return;
    }

    // pause condition
    if (dummy->name == "Default" || Wallet_List[index]->name == "Cash")
    {
        cout << " [Error] Cannot delete the Default/System wallet.\n";
        system("pause");
        return;
    }

    if (Is_Wallet_In_Use(id))
    {
        cout << " [CRITICAL] Cannot delete this wallet!\n";
        cout << " Reason: It contains existing transactions or recurring settings.\n";
        cout << " Solution: Delete all transactions related to this wallet first.\n";
        system("pause");
        return;
    }

    //  Xóa
    delete Wallet_List[index];
    for (int i = index; i < wallet_count - 1; i++)
    {
        Wallet_List[i] = Wallet_List[i + 1];
    }
    wallet_count--; // Giảm số ví

    cout << " [Success] Wallet deleted successfully.\n";
    system("pause");
}

void User_Info::Edit_ExpenseCategory()
{

    cout << "\n--- Expense Categories ---\n";
    for (int i = 0; i < expense_count; i++)
        cout << "ID: " << expense[i]->id << " | " << expense[i]->name << endl;

    int id;
    cout << "Enter ID to Edit: ";
    cin >> id;
    Clear_Buffer();

    ExpenseCategory *target = nullptr;
    if (!Find_By_ID(id, expense, expense_count, target))
    {
        cout << "ID not found.\n";
        return;
    }

    cout << "Enter New Name: ";
    string newName;
    getline(cin, newName);
    if (!newName.empty() && !check_string(newName, '^'))
    {
        target->name = newName;
        cout << "Updated.\n";
    }
}

void User_Info::Delete_ExpenseCategory()
{

    cout << "\n--- Expense Categories ---\n";
    for (int i = 0; i < expense_count; i++)
        cout << "ID: " << expense[i]->id << " | " << expense[i]->name << endl;

    int id;
    string input;
    bool check=true;
    ExpenseCategory *dummy;
    while(check)
    {
    cout << "Enter Expense Category ID to Delete: ";
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
        if(id==0 || !Find_By_ID(id, expense, expense_count, dummy))
        {
            cout << "Error: Please Input an valid ID.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
        else
        check=false;
    }
    }
    int index = -1;
    for (int i = 0; i < expense_count; i++)
    {
        if (expense[i]->id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "ID not found.\n";
        return;
    }

    if (expense[index]->name == "Unknown")
    {
        cout << "Cannot delete system category.\n";
        return;
    }

    // check
    if (Is_Category_In_Use(id))
    {
        cout << " [Error] Cannot delete! Category is used in transactions.\n";
        system("pause");
        return;
    }

    // xóa
    delete expense[index];
    for (int i = index; i < expense_count - 1; i++)
    {
        expense[i] = expense[i + 1];
    }
    expense_count--;
    cout << "Deleted successfully.\n";
    system("pause");
}

void User_Info::Edit_IncomeSource()
{
    cout << "\n--- Income Sources ---\n";
    for (int i = 0; i < income_count; i++)
        cout << "ID: " << income[i]->id << " | " << income[i]->name << endl;

    int id;
    cout << "Enter ID to Edit: ";
    cin >> id;
    Clear_Buffer();

    IncomeSource *target = nullptr;
    if (!Find_By_ID(id, income, income_count, target))
    {
        cout << "ID not found.\n";
        return;
    }

    cout << "Enter New Name: ";
    string newName;
    getline(cin, newName);
    if (!newName.empty() && !check_string(newName, '^'))
    {
        target->name = newName;
        cout << "Updated.\n";
    }
}

void User_Info::Delete_IncomeSource()
{
    cout << "\n--- Income Sources ---\n";
    for (int i = 0; i < income_count; i++)
        cout << "ID: " << income[i]->id << " | " << income[i]->name << endl;

    int id;
    cout << "Enter ID to Delete: ";
    cin >> id;
    Clear_Buffer();

    int index = -1;
    for (int i = 0; i < income_count; i++)
    {
        if (income[i]->id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "ID not found.\n";
        return;
    }

    if (income[index]->name == "Unknown")
    {
        cout << "Cannot delete system source.\n";
        return;
    }

    // Check
    if (Is_Source_In_Use(id))
    {
        cout << " [Error] Cannot delete! Source is used in transactions.\n";
        system("pause");
        return;
    }

    // xóa
    delete income[index];
    for (int i = index; i < income_count - 1; i++)
    {
        income[i] = income[i + 1];
    }
    income_count--;
    cout << "Deleted successfully.\n";
    system("pause");
}

void User_Info::Draw_MasterData_Menu()
{
    while (true)
    {
        system("cls");
        cout << "====================================\n";
        cout << "    DON'T KNOW WHAT IT IS CALLED    \n";
        cout << "====================================\n";
        cout << " 1. Add Expense Category\n";
        cout << " 2. Edit Expense Category\n";
        cout << " 3. Delete Expense Category\n";
        cout << " -----------------------------------\n";
        cout << " 4. Add Income Source\n";
        cout << " 5. Edit Income Source\n";
        cout << " 6. Delete Income Source\n";
        cout << " -----------------------------------\n";
        cout << " 0. Back\n";
        cout << "====================================\n";
        cout << " Select: ";
        int c;
        cin >> c;
        Clear_Buffer();

        switch (c)
        {
        case 1:
            Add_Expense();
            system("pause");
            break;
        case 2:
            Edit_ExpenseCategory();
            system("pause");
            break;
        case 3:
            Delete_ExpenseCategory();
            break;
        case 4:
            Add_Income();
            system("pause");
            break;
        case 5:
            Edit_IncomeSource();
            system("pause");
            break;
        case 6:
            Delete_IncomeSource();
            break;
        case 0:
            return;
        default:
            break;
        }
    }
}