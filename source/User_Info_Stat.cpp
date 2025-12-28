#include "../header/User_Info.h"

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
    for (int i = 0; i < recur_trans_income_count; i++)
    {
        if (Recurring_Transaction_Income_List[i]->wallet->id == id)
            return true;
    }
    // Check recurring expense
    for (int i = 0; i < recur_trans_expense_count; i++)
    {
        if (Recurring_Transaction_Expense_List[i]->wallet->id == id)
            return true;
    }
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
    clearScreen();
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
    clearScreen();
    Show_Wallet_List();
    int id;
    string input;
    bool check = true;
    Wallet *dummy;
    while (check)
    {
        cout << "Enter Wallet ID to Delete: ";
        cin >> input;

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
            id = stoi(input);
            if (!Find_By_ID(id, Wallet_List, wallet_count, dummy))
            {
                cout << "Error: Please Input an valid ID.\n";
                system("pause");
                return;
            }
            else
                check = false;
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

void User_Info::Switch_Wallet()
{
    Show_Wallet_List();
    int id;
    string input;
    bool check = true;
    Wallet *dummy;
    while (check)
    {
        cout << "Enter Wallet ID to set default: ";
        cin >> input;

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
            id = stoi(input);
            if (!Find_By_ID(id, Wallet_List, wallet_count, dummy))
            {
                cout << " [Error] Cannot find wallet with ID: " << id << endl;
                system("pause");
                return;
            }
            else
                check = false;
        }
    }
    Clear_Buffer();

    //  Switch
    this->default_Wallet = dummy;
    cout << " [Success] Default Wallet set to: " << this->default_Wallet->name << endl;
    system("pause");
}

void User_Info::Edit_ExpenseCategory()
{

    cout << "\n--- Expense Categories ---\n";
    for (int i = 0; i < expense_count; i++)
        cout << "ID: " << expense[i]->id << " | " << expense[i]->name << endl;
    int id;
    string input;
    bool check = true;
    ExpenseCategory *dummy;
    while (check)
    {
        cout << "Enter Expense Category ID to Delete: ";
        cin >> input;

        if (!isValidInt(input))
        {
            cout << "Error: Please Input an valid ID.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
        else
        {
            id = stoi(input);
            if (!Find_By_ID(id, expense, expense_count, dummy))
            {
                cout << "Error: Please Input an valid ID.\n";
                system("pause");
                return;
            }
            else
                check = false;
        }
    }

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
    bool check = true;
    ExpenseCategory *dummy;
    while (check)
    {
        cout << "Enter Expense Category ID to Delete: ";
        cin >> input;

        if (!isValidInt(input))
        {
            cout << "Error: Please Input an valid ID.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
        else
        {
            id = stoi(input);
            if (!Find_By_ID(id, expense, expense_count, dummy))
            {
                cout << "Error: Please Input an valid ID.\n";
                system("pause");
                return;
            }
            else
                check = false;
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
    string input;
    bool check = true;
    ExpenseCategory *dummy;
    while (check)
    {
        cout << "Enter Expense Category ID to Delete: ";
        cin >> input;

        if (!isValidInt(input))
        {
            cout << "Error: Please Input an valid ID.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
        else
        {
            id = stoi(input);
            if (!Find_By_ID(id, expense, expense_count, dummy))
            {
                cout << "Error: Please Input an valid ID.\n";
                system("pause");
                return;
            }
            else
                check = false;
        }
    }

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
    string input;
    bool check = true;
    ExpenseCategory *dummy;
    while (check)
    {
        cout << "Enter Expense Category ID to Delete: ";
        cin >> input;

        if (!isValidInt(input))
        {
            cout << "Error: Please Input an valid ID.\n";
            cout << "Press enter to retype...";
            cin.get();
            Clear_Buffer();
            ClearLines(3);
        }
        else
        {
            id = stoi(input);
            if (!Find_By_ID(id, expense, expense_count, dummy))
            {
                cout << "Error: Please Input an valid ID.\n";
                system("pause");
                return;
            }
            else
                check = false;
        }
    }

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
        system("pause");
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
        cout << "       MASTER DATA MANAGEMENT       \n";
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
        int choice;
        if (!Input_Choice(choice))
        {
            cout << "\n[!] Invalid input. Please enter a number.\n";
            pause();
            continue;
        }

        switch (choice)
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