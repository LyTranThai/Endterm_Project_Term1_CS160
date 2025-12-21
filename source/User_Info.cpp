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

    void User_Info::Show_Wallet_List()
    {

    }
    void Show_Transaction_History();
    void Show_Recurring_Transaction_List();
    void User_Info::Add_Wallet()
    {
        Wallet dummy;
        this->resize();
        while (true) 
        {
        cout << "Enter your new wallet name: ";
        if (cin.peek() == '\n') cin.ignore(); 
        getline(cin, dummy.name);


        if (dummy.name.empty() || check_string(dummy.name, '^')) 
        {
            cout << "Invalid name (cannot be empty or contain '^'). Try again.\n";
            continue;
        }

        Wallet* save = nullptr;
        // Check for duplicate name
        if (Find_By_Name(dummy.name, this->Wallet_List, this->wallet_count, save)) {
            cout << "Wallet name existed, please choose another name.\n";
        } else {
            break; // Name is valid and unique
        }
        }

        // Loop for Balance Input (Robust check)
        string s;
        long long validBalance = 0;
        while (true) {
        cout << "Enter your balance: ";
        cin >> s; // No spaces allowed in numbers, so cin is fine here

        // Use your existing helper
        if (isValidLongLong(s)) {
            validBalance = stoll(s);
            break;
        } else {
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
        if (cin.peek() == '\n') cin.ignore(); 
        getline(cin, new_name);

        // Validation 1: Empty or Invalid Char
        if (new_name.empty() || check_string(new_name, '^'))
        {
            cout << "Invalid name. Cannot be empty or contain '^'. Try again.\n";
            continue;
        }

        // Validation 2: Duplicates
        ExpenseCategory* temp = nullptr;
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

        if (cin.peek() == '\n') cin.ignore(); 
        getline(cin, new_name);

        if (new_name.empty() || check_string(new_name, '^'))
        {
            cout << "Invalid name. Cannot be empty or contain '^'. Try again.\n";
            continue;
        }

        IncomeSource* temp = nullptr;
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
        this->resize(); // Ensure we have space before starting

        // --- STEP 1: DATE ---
        string dateStr;
        Date transDate;
        do 
        {
            cout << "Enter Date of transaction (dd/mm/yyyy): ";
            // Optional: Clean buffer if coming from previous cin input
            if (cin.peek() == '\n') cin.ignore(); 
            getline(cin, dateStr);
            transDate = InputDate(dateStr);

            if (transDate.day == 0) {
                cout << "Invalid date format! Please try again (e.g., 25/12/2023).\n";
            }
        } while (transDate.day == 0);


        // --- STEP 2: EXPENSE CATEGORY ---
        string type_name;
        ExpenseCategory* dummy_EC = nullptr;
        bool check_EC = true;
        int choice;

        while (check_EC)
        {
            // Loop to get a valid name string
            while(true)
            {
                cout << "Enter your expense category name (e.g., Food): ";
                if (cin.peek() == '\n') cin.ignore(); 
                getline(cin, type_name);

                if (type_name.empty() || check_string(type_name, '^'))
                {
                    cout << "Invalid name. Cannot be empty or contain '^'. Try again.\n";
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
                cout << "1. Yes\n2. No\n0. Cancel\nChoice: ";
                cin >> choice;

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
                    break;
                }
                case 2:
                    cout << "Please choose an existing category or create a new one.\n";
                    break;
                case 0:
                    return; // Exit function
                default:
                    cout << "Invalid choice.\n";
                    break;
                }
            }
        }


        // --- STEP 3: AMOUNT ---
        string s;
        long long validAmount = 0;
        while (true) 
        {
            cout << "Enter expense amount: ";
            cin >> s; 

            if (isValidLongLong(s)) {
                validAmount = stoll(s);
                if (validAmount < 0) {
                    cout << "Amount cannot be negative. Enter a positive value (it will be subtracted).\n";
                    continue;
                }
                break;
            } else {
                cout << "Invalid amount. Please enter a valid integer.\n";
            }
        }


        // --- STEP 4: WALLET ---
        Wallet dummy;
        Wallet* dummy_W = nullptr;
        bool check_W = true;

        while(check_W)
        {
            while (true) 
            {
                cout << "Enter wallet name to pay from: ";
                if (cin.peek() == '\n') cin.ignore(); 
                getline(cin, dummy.name);

                if (dummy.name.empty() || check_string(dummy.name, '^')) 
                {
                    cout << "Invalid name. Try again.\n";
                    continue;
                }
                break;
            }

            // Find Wallet
            if (Find_By_Name(dummy.name, this->Wallet_List, this->wallet_count, dummy_W)) 
            {
                // Optional: Warning if balance will go negative
                if (dummy_W->remain < validAmount) {
                    cout << "Warning: This expense will make the wallet balance negative.\n";
                }
                cout << "Wallet chosen: " << dummy.name << endl;
                check_W = false;
            } 
            else 
            {
                cout << "Wallet not found. Create new?\n1. Yes\n2. No\n0. Cancel\nChoice: ";
                cin >> choice;
                
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
                    cout << " New Wallet Created (Balance: 0)" << endl;
                    cout << "---------------------------------" << endl;
                    check_W = false;
                    break;
                }
                case 2: 
                    break;
                case 0: 
                    return;
                default: 
                    cout << "Invalid choice.\n";
                    break;
                }
            }
        }

        // --- STEP 5: DESCRIPTION ---
        string Des_Input;
        cout << "Enter description: ";
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, Des_Input);


        // --- STEP 6: SAVE & UPDATE BALANCE ---
        this->resize(); // Final check for array capacity

        expenses_transaction[expCount] = new Transaction_Expense;
        expenses_transaction[expCount]->date = transDate;
        expenses_transaction[expCount]->type = dummy_EC;
        expenses_transaction[expCount]->wallet = dummy_W;
        expenses_transaction[expCount]->amount = validAmount;
        expenses_transaction[expCount]->description = Des_Input;

        // CRITICAL DIFFERENCE: SUBTRACT MONEY
        dummy_W->remain -= validAmount;

        expCount++;
        
        cout << "Expense Transaction Added Successfully!\n";
        cout << "New Balance of " << dummy_W->name << ": " << dummy_W->remain << endl;
    }
    void User_Info::Add_Income_Transaction()
    {   
        string dateStr;
        //DATE
        Date transDate;
        // --- INPUT LOOP TO GET DATE---
        do 
        {
            if (cin.peek() == '\n') cin.ignore();
            cout << "Enter Date of transaction (dd/mm/yyyy): ";
            getline(cin, dateStr);
            transDate = InputDate(dateStr);

            if (transDate.day == 0) {
                cout << "Invalid date format or logic! Please try again (e.g., 25/12/2023).\n";
            }
        } while (transDate.day == 0);

        string type_name;
        //INCOME SOURCE POINTER
        IncomeSource* dummy_IS = nullptr;
        int choice;
        bool check_IS=true;
        // --- INPUT LOOP TO GET INCOME SOURCE---
        while (check_IS)
        {
            while(true)
            {
                cout << "Enter your income source name (e.g., Salary): ";
                //Show_Income_Source();
                //This will draw all the Incomsource on for user to choose
                if (cin.peek() == '\n') cin.ignore(); 
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
            string new_name=type_name;

            
            // Using Find_By_Name to check duplicates in the income array
            if (Find_By_Name(type_name, this->income, this->income_count, dummy_IS))
            {
                cout << "Source chosen successfully: "<< type_name<<endl;
                check_IS=false;
            }
            else
            {
                cout<< "Income source does not exist, do you want to create a new incoce source?\n";
                cout<< "Enter your choice (1/0): \n";
                cout<< "1. Yes\n";
                cout<< "2. No\n";
                cout<< "0. Back to menu\n";
                //Clear buffer here also, Write me a function for clear buffer specifically
                cin>>choice;
                int new_IS_id;
                switch (choice)
                {
                case 1:
                    //Auto add a income source here
                    //name: new_name
                    //ID: auto generate
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
                    check_IS=false;
                    break;
                
                case 2:
                    cout << "Invalid Income Source\n";
                    cout << "Press enter to go back...";
                    cin.get();
                    // User decline so we go back to ask them to type the name again
                    break;
                case 0:
                    cout<< "Invalid transaction\n";
                    cout << "Press enter to go back...";
                    cin.get();
                    return;
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
        while (true) {
        cout << "Enter your amount of transaction: ";
        cin >> s; // No spaces allowed in numbers, so cin is fine here

        // Use your existing helper
        if (isValidLongLong(s)) {
            cout<<"Your amount is valid!"<<endl;
            validAmount = stoll(s);
            break;
        } else {
            cout << "Invalid amount. Please enter a valid integer number.\n";
        }
        }
        // --- INPUT LOOP TO GET WALLET---
        //dummy for getting input
        Wallet dummy;
        bool check_W=true;
        //Dummy pointer for later linking
        Wallet* dummy_W = nullptr;
        while(check_W)
        {
        while (true) 
        {
            cout << "Enter your new wallet name: ";
            //Show_Wallet();
            //Draw all Wallet for user to choose
            if (cin.peek() == '\n') cin.ignore(); 
            getline(cin, dummy.name);


            if (dummy.name.empty() || check_string(dummy.name, '^')) 
            {
                cout << "Invalid name (cannot be empty or contain '^'). Try again.\n";
                continue;
            }

            
            // Find Wallet
            if (Find_By_Name(dummy.name, this->Wallet_List, this->wallet_count, dummy_W)) 
            {
                cout << "Wallet chosen successfully: "<< dummy.name<<endl;
                check_W=false;
            } 
            else 
            {
                cout<< "Wallet does not exist, do you want to create a new Wallet?\n";
                cout<< "Enter your choice (1/0): \n";
                cout<< "1. Yes\n";
                cout<< "2. No\n";
                cout<< "0. Back to menu";
                //Clear buffer here also, Write me a function for clear buffer specifically
                int new_W_id;
                cin>>choice;
                switch (choice)
                {
                case 1:
                    //Auto add a Wallet here
                    //name: new_name
                    //ID: auto generate
                    //Balance = 0;
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
                    check_W=false;
                    break;
                
                case 2:
                    cout << "Invalid Wallet\n";
                    cout << "Press enter to go back...";
                    cin.get();
                    // User decline so we go back to ask them to type the name again
                    break;
                case 0:
                    cout<< "Invalid transaction\n";
                    cout << "Press enter to go back...";
                    cin.get();
                    return;
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
        string Des_Input;
        cout<<"Enter your description, press enter to finish: ";
        getline(cin, Des_Input);

        resize();
        incomes_transaction[inCount]=new Transaction_Income;
        incomes_transaction[inCount]->date=transDate;
        incomes_transaction[inCount]->type=dummy_IS;
        incomes_transaction[inCount]->wallet=dummy_W;
        incomes_transaction[inCount]->amount=validAmount;
        incomes_transaction[inCount]->wallet->remain += validAmount;
        incomes_transaction[inCount]->description=Des_Input;
        cout<<"New Transaction Added\n";
        //prinout all the informatuin one more time for the user to check
        inCount +=1;


    }
void User_Info::Add_Recur_Expense_Transaction()
{
    this->resize(); // Ensure capacity

    // --- STEP 1: START DATE ---
    string dateStr;
    Date startDate;
    do 
    {
        cout << "Enter Start Date (dd/mm/yyyy): ";
        if (cin.peek() == '\n') cin.ignore(); 
        getline(cin, dateStr);
        startDate = InputDate(dateStr);

        if (startDate.day == 0) {
            cout << "Invalid date format! Please try again.\n";
        }
    } while (startDate.day == 0);


    // --- STEP 2: END DATE ---
    Date endDate;
    while (true)
    {
        cout << "Enter End Date (dd/mm/yyyy): ";
        // We don't need cin.ignore() here because the previous loop ended with getline
        getline(cin, dateStr);
        endDate = InputDate(dateStr);

        if (endDate.day == 0) {
            cout << "Invalid date format! Please try again.\n";
            continue;
        }

        // Logic Check: End Date must be >= Start Date
        // Using your compare function: returns positive if date1 > date2
        if (compare(endDate, startDate) < 0) {
            cout << "Error: End Date cannot be before Start Date.\n";
        } else {
            break; // Valid date
        }
    }


    // --- STEP 3: EXPENSE CATEGORY ---
    string type_name;
    ExpenseCategory* dummy_EC = nullptr;
    bool check_EC = true;
    int choice;

    while (check_EC)
    {
        while(true)
        {
            cout << "Enter expense category name (e.g., Rent): ";
            getline(cin, type_name);

            if (type_name.empty() || check_string(type_name, '^'))
            {
                cout << "Invalid name. Try again.\n";
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
            cout << "Category does not exist. Create new?\n1. Yes\n2. No\n0. Cancel\nChoice: ";
            cin >> choice;
            if (cin.peek() == '\n') cin.ignore(); // Clear buffer after cin >> choice

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

                cout << "New Category Created: " << type_name << endl;
                check_EC = false;
                break;
            }
            case 2: break;
            case 0: return;
            default: cout << "Invalid choice.\n"; break;
            }
        }
    }


    // --- STEP 4: AMOUNT ---
    string s;
    long long validAmount = 0;
    while (true) 
    {
        cout << "Enter recurring amount: ";
        cin >> s; 

        if (isValidLongLong(s)) {
            validAmount = stoll(s);
            if (validAmount < 0) {
                cout << "Amount must be positive.\n";
                continue;
            }
            break;
        }
        cout << "Invalid integer amount.\n";
    }


    // --- STEP 5: WALLET ---
    Wallet dummy;
    Wallet* dummy_W = nullptr;
    bool check_W = true;

    while(check_W)
    {
        while (true) 
        {
            cout << "Enter wallet name: ";
            if (cin.peek() == '\n') cin.ignore(); 
            getline(cin, dummy.name);

            if (dummy.name.empty() || check_string(dummy.name, '^')) 
            {
                cout << "Invalid name.\n";
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
            cout << "Wallet not found. Create new?\n1. Yes\n2. No\n0. Cancel\nChoice: ";
            cin >> choice;
            if (cin.peek() == '\n') cin.ignore(); 

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
                break;
            }
            case 2: break;
            case 0: return;
            default: cout << "Invalid choice.\n"; break;
            }
        }
    }

    // --- STEP 6: DESCRIPTION ---
    string Des_Input;
    cout << "Enter description: ";
    // Previous input was cin >> s or cin >> choice, buffer might be clean if we used ignore(), 
    // but safe to check peek just in case logic flow skipped an ignore
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, Des_Input);


    // --- STEP 7: SAVE (NO BALANCE UPDATE) ---
    this->resize(); 

    // Accessing the Recurring List
    Recurring_Transaction_Expense_List[recur_trans_expense_count] = new Recurring_Transaction_Expense;
    
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->start = startDate;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->end = endDate;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->type = dummy_EC;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->wallet = dummy_W;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->amount = validAmount;
    Recurring_Transaction_Expense_List[recur_trans_expense_count]->description = Des_Input;

    // NOTE: Wallet balance (remain) is NOT updated here, as requested.

    recur_trans_expense_count++;
    
    cout << "---------------------------------------" << endl;
    cout << " Recurring Expense Scheduled! " << endl;
    cout << " From: "; OutputDate(startDate); cout << endl;
    cout << " To:   "; OutputDate(endDate);   cout << endl;
    cout << "---------------------------------------" << endl;
}



void User_Info::Add_Recur_Income_Transaction()
{
    this->resize(); // Ensure capacity exists

    // --- STEP 1: START DATE ---
    string dateStr;
    Date startDate;
    do 
    {
        cout << "Enter Start Date (dd/mm/yyyy): ";
        if (cin.peek() == '\n') cin.ignore(); 
        getline(cin, dateStr);
        startDate = InputDate(dateStr);

        if (startDate.day == 0) {
            cout << "Invalid date format! Please try again.\n";
        }
    } while (startDate.day == 0);


    // --- STEP 2: END DATE ---
    Date endDate;
    while (true)
    {
        cout << "Enter End Date (dd/mm/yyyy): ";
        // Previous loop ended with getline, buffer is clean
        getline(cin, dateStr);
        endDate = InputDate(dateStr);

        if (endDate.day == 0) {
            cout << "Invalid date format! Please try again.\n";
            continue;
        }

        // Logic Check: End Date must be >= Start Date
        if (compare(endDate, startDate) < 0) {
            cout << "Error: End Date cannot be before Start Date.\n";
        } else {
            break; // Valid date
        }
    }


    // --- STEP 3: INCOME SOURCE ---
    string type_name;
    IncomeSource* dummy_IS = nullptr;
    bool check_IS = true;
    int choice;

    while (check_IS)
    {
        while(true)
        {
            cout << "Enter income source name (e.g., Salary): ";
            getline(cin, type_name);

            if (type_name.empty() || check_string(type_name, '^'))
            {
                cout << "Invalid name. Try again.\n";
                continue;
            }
            break;
        }

        // Check against Income Array
        if (Find_By_Name(type_name, this->income, this->income_count, dummy_IS))
        {
            cout << "Source chosen: " << type_name << endl;
            check_IS = false;
        }
        else
        {
            cout << "Source does not exist. Create new?\n1. Yes\n2. No\n0. Cancel\nChoice: ";
            cin >> choice;
            if (cin.peek() == '\n') cin.ignore(); 

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
                break;
            }
            case 2: break;
            case 0: return;
            default: cout << "Invalid choice.\n"; break;
            }
        }
    }


    // --- STEP 4: AMOUNT ---
    string s;
    long long validAmount = 0;
    while (true) 
    {
        cout << "Enter recurring amount: ";
        cin >> s; 

        if (isValidLongLong(s)) {
            validAmount = stoll(s);
            if (validAmount < 0) {
                cout << "Amount must be positive.\n";
                continue;
            }
            break;
        }
        cout << "Invalid integer amount.\n";
    }


    // --- STEP 5: WALLET ---
    Wallet dummy;
    Wallet* dummy_W = nullptr;
    bool check_W = true;

    while(check_W)
    {
        while (true) 
        {
            cout << "Enter target wallet name: ";
            if (cin.peek() == '\n') cin.ignore(); 
            getline(cin, dummy.name);

            if (dummy.name.empty() || check_string(dummy.name, '^')) 
            {
                cout << "Invalid name.\n";
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
            cout << "Wallet not found. Create new?\n1. Yes\n2. No\n0. Cancel\nChoice: ";
            cin >> choice;
            if (cin.peek() == '\n') cin.ignore(); 

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
                break;
            }
            case 2: break;
            case 0: return;
            default: cout << "Invalid choice.\n"; break;
            }
        }
    }

    // --- STEP 6: DESCRIPTION ---
    string Des_Input;
    cout << "Enter description: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, Des_Input);


    // --- STEP 7: SAVE (NO BALANCE UPDATE) ---
    this->resize(); 

    // Accessing the Recurring Income List
    Recurring_Transaction_Income_List[recur_trans_income_count] = new Recurring_Transaction_Income;
    
    Recurring_Transaction_Income_List[recur_trans_income_count]->start = startDate;
    Recurring_Transaction_Income_List[recur_trans_income_count]->end = endDate;
    Recurring_Transaction_Income_List[recur_trans_income_count]->type = dummy_IS;
    Recurring_Transaction_Income_List[recur_trans_income_count]->wallet = dummy_W;
    Recurring_Transaction_Income_List[recur_trans_income_count]->amount = validAmount;
    Recurring_Transaction_Income_List[recur_trans_income_count]->description = Des_Input;

    // NOTE: Wallet balance (remain) is NOT updated here.

    recur_trans_income_count++;
    
    cout << "---------------------------------------" << endl;
    cout << " Recurring Income Scheduled! " << endl;
    cout << " From: "; OutputDate(startDate); cout << endl;
    cout << " To:   "; OutputDate(endDate);   cout << endl;
    cout << "---------------------------------------" << endl;
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