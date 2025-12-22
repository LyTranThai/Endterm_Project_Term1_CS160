#include <iostream>
#include "../header/User_Info.h"

using namespace std;
//MUST RUN TO INPUT CURRENCY DATA 
// int main()
// {
// //Create Currency List
//     Currency * Currency_Type=new Currency[3];
//     Input_Currency("currency",Currency_Type);
//     delete[]Currency_Type;
//     return 0;
// }


#include <vector>
#include <string>
#include <iomanip> // For formatting tables
#include <fstream> // For File I/O
#include <limits>  // For input cleaning


using namespace std;
bool Input_Choice(int& choice)
{
string input;
getline(cin, input); 

try {
    choice = stoi(input);
    return true; // Try to convert string to int
} 
catch (...) {
    return false; // reset
}
}

//Clear screen
void clearScreen()
{
    // If you are on Windows, use "cls". If on Mac/Linux, use "clear"
    #ifdef _WIN32
        system("cls");
    #endif
}

//Wait for the user to press something
void pause()
{
      cout << "\nPress Enter to continue...";
    // This line clears any leftover "Enter" keys in the keyboard buffer
    // This line waits for a NEW "Enter" key press
    cin.get();
}


void drawMenu(User_Info& user) //ifstream& fin
{
    int window_width=70;
    string userName=user.name;
    string currentWallet=user.default_Wallet->name;
    double currentRemainder=10000;

    // 1. Header & User Info
    cout << string(window_width, '=')<<endl;
    print_center("PERSONAL FINANCE MANAGER", ' ', window_width); cout << endl;
    cout << string(window_width, '=')<<endl;
    
    // Display dynamic info (Name, Wallet, Remainder)
    cout << " User:      " << userName << "\n";
    cout << " Wallet:    " << currentWallet << "\n";
    cout << " Remainder: $" << fixed << setprecision(2) << currentRemainder << "\n"; 
    cout << string(window_width, '-')<<endl;

    // 2. Selectable Options
    cout << "1. Wallet List (Switch/View Wallets)\n";
    cout << "2. Transaction History\n";
    cout << "3. Add Transaction (Update)\n";//Recurring and normal Transaction
    cout << "4. Recurring Transaction List\n";
    cout << "5. Save Progress\n";
    cout << "6. Exit (Auto-Save & End)\n";
    cout << string(window_width, '-')<<endl;
    cout << "Select option: ";
}

void Draw_Wallet_List(User_Info& user)
{
    int window_width=70;

    // 1. Header & User Info
    cout << string(window_width, '=')<<endl;
    print_center("PERSONAL FINANCE MANAGER", ' ', window_width); cout << endl;
    cout << string(window_width, '=')<<endl;
    print_center("WALLET LIST", ' ', window_width); cout << endl;
    cout << string(window_width, '=')<<endl;
    user.Show_Wallet_List();
    // 2. Selectable Options
    cout << "1. Choose Wallet (Set as Default/Adjust/Delete)\n";
    cout << "2. Add Wallet\n";
    cout << "0. Back to menu\n";
    cout << string(window_width, '-')<<endl;
    cout << "Select option: ";
}    // 1.Change Wallet 2. back
void Draw_Transaction_History(User_Info& user)
{
    int window_width=70;

    // 1. Header & User Info
    cout << string(window_width, '=')<<endl;
    print_center("PERSONAL FINANCE MANAGER", ' ', window_width); cout << endl;
    cout << string(window_width, '=')<<endl;
    print_center("TRANSACTION HISTORY", ' ', window_width); cout << endl;
    cout << string(window_width, '=')<<endl;
    user.Show_Transaction_History();
    // 2. Selectable Options
    cout << "1. Add Transaction\n";
    cout << "0. Back to menu\n";
    cout << string(window_width, '-')<<endl;
    cout << "Select option: ";
}
void Draw_Add_Transaction(User_Info& user)
{
    int window_width=70;

    // 1. Header & User Info
    cout << string(window_width, '=')<<endl;
    print_center("PERSONAL FINANCE MANAGER", ' ', window_width); cout << endl;
    cout << string(window_width, '=')<<endl;
    print_center("ADD TRANSACTION", ' ', window_width); cout << endl;
    cout << string(window_width, '=')<<endl;
    user.Show_Transaction_History();
    // 2. Selectable Options
    cout << "1. Add Income Transaction\n";
    cout << "2. Add Expense Transaction\n";
    cout << "0. Back to menu\n";
    cout << string(window_width, '=')<<endl;
    cout << "Select option: ";
}
void Draw_Recurring_Transaction_List(User_Info& user)
{
    int window_width=70;

    // 1. Header & User Info
    cout << string(window_width, '=')<<endl;
    print_center("PERSONAL FINANCE MANAGER", ' ', window_width); cout << endl;
    cout << string(window_width, '=')<<endl;
    print_center("RECURRING TRANSACTION LIST", ' ', window_width); cout << endl;
    cout << string(window_width, '=')<<endl;
    user.Show_Recurring_Transaction_List();
    // 2. Selectable Options
    cout << "1. Add Income Recurring Transaction\n";
    cout << "2. Add Expense Recurring Transaction\n";
    cout << "0. Back to menu\n";
    cout << "-------------------------------------------------\n";
    cout << "Select option: ";
}
bool Input_Choice(int& choice);
void Input_User_Info_Textfile(string filename);

// Income Management:
// ▪ Users enter information for an income transaction.
// ▪ Required Data:
// ▪ Date: The date the transaction is executed.
// ▪ Income Source: The system stores the Source ID for logic processing but displays the
// Source Name on the user interface.
// ▪ Amount: The value of the income.
// ▪ Wallet: The system stores the Wallet ID but displays the Wallet Name.
// ▪ Description: Detailed notes for the income.
// o Expense Management:
// ▪ Users enter information for expense transactions.
// ▪ Required Data:
// ▪ Date: The date the transaction is executed.
// ▪ Income Source: the system stores the Category ID but displays the Category Name.
// ▪ Amount: The value of the expense.
// ▪ Wallet: The system stores the Wallet ID but displays the Wallet Name.
// ▪ Description: Detailed notes for the expense.



// Support automation for entering frequently recurring income or expenses.
// o Recurring Configuration: Allow pre-creation of recurring transactions on Monthly basis.
// o Applicable Time:
// ▪ Start Date: Required.
// ▪ End Date: Optional (Can be left blank if the transaction recurs indefinitely).
// o Mechanism: When the user opens the application, the system checks and adds the transaction for
// the current month if the conditions are met, ensuring that the transaction is not added again if it
// already exists for the current cycle.
void RunApplication_Navigation(User_Info& user)
{
    ofstream fout;
    while (true)
    {
        int choice;
        clearScreen();
        drawMenu(user);
        if(!Input_Choice(choice))
        {
            cout << "\n[!] Invalid input. Please enter a number.\n";
            pause();
            continue;
        }
        switch (choice)
        {
            case 1:
                Draw_Wallet_List(user);
                break;
            case 2:
                Draw_Transaction_History(user);
                break;
            case 3:
                Draw_Add_Transaction(user);
                break;
            case 4:
                Draw_Recurring_Transaction_List(user);
                break;
            case 5:
                fout.open("../UserData/"+user.name+".bin",ios::binary|ios::trunc);
                user.SaveToBinary(fout);
                cout << "\nSaving progress...\n";
                pause();
                break;
            case 6:
                cout << "\nExiting application. Goodbye!\n";
                return; // Breaks the loop and ends the program
            default:
                cout << "\n[!] Option not found.\n";
                pause();
                // Loop will automatically restart here, resetting the UI
                break; 
        }

    }
    
}



int main()
{
    // 1. Setup Interface
    clearScreen();
    cout << endl;
    cout << "=================================================\n";
    cout << "              FINANCIAL TRACKER APP              \n";
    cout << "=================================================\n";
    cout << "Type in your name (no spaces): ";
    
    string name;
    cin >> name;
    Clear_Buffer(); // Clear newline left by cin >> name

    // 2. Define File Path
    // Ensure the "UserData" folder exists relative to your exe, or create it manually.
    string filename = "../UserData/" + name + ".bin";
    
    User_Info user; // Constructor runs here (initializes Default Wallet, Unknown Categories)

    // 3. Check if file exists
    ifstream fin(filename, ios::binary);

    if (fin.is_open()) 
    {
        cout << "\n [!] Welcome back, " << name << "! Loading your data...\n";
        
        // LOAD DATA
        user.LoadFromBinary(fin);
        fin.close();

        // 4. CHECK RECURRING TRANSACTIONS (Requirement: Check on startup)
        Date today;
        GetCurrentDate(today); // Assumed function from Date.h
        
        bool auto_updates = false;
        
        // Check Recurring Expenses
        for(int i = 0; i < user.recur_trans_expense_count; i++) {
             if(user.check_recur_trans(user.Recurring_Transaction_Expense_List[i], today)) {
                 auto_updates = true;
             }
        }
        
        // Check Recurring Incomes
        for(int i = 0; i < user.recur_trans_income_count; i++) {
             if(user.check_recur_trans(user.Recurring_Transaction_Income_List[i], today)) {
                 auto_updates = true;
             }
        }

        if(auto_updates) {
            cout << " [!] Automatic recurring transactions have been generated for this month.\n";
            cout << "     Press Enter to continue...";
            cin.get();
        }
    } 
    else 
    {
        cout << "\n [!] New user detected. Creating profile for " << name << "...\n";
        user.name = name;
        
        // SAVE DEFAULTS IMMEDIATELY
        // This ensures the file exists with the default "Default" wallet
        ofstream fout(filename, ios::binary);
        if (fout.is_open()) {
            user.SaveToBinary(fout);
            fout.close();
            cout << " [!] Profile created successfully.\n";
        } else {
            cerr << " [Error] Could not create file at: " << filename << endl;
            cerr << "         Please ensure the folder '../UserData' exists.\n";
            system("pause");
            return 1;
        }
        
        cout << " Press Enter to start...";
        cin.get();
    }

    // 5. Run Application
    RunApplication_Navigation(user);

    return 0;
}