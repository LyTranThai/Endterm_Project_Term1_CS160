#include <iostream>
#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Currency.h"
#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Date.h"
#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Transaction_Type.h"
#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Transaction.h"
#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Wallet.h"
#include "Currency.cpp"
using namespace std;

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
void Input_Choice(int& choice)
{
string input;
getline(cin, input); 

try {
    choice = stoi(input); // Try to convert string to int
} 
catch (...) {
    choice = -1; // If conversion fails, set to an invalid number
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // This line waits for a NEW "Enter" key press
    cin.get();
}

void drawMenu(ifstream& fin) 
{
    string userName;
    string currentWallet;
    double currentRemainder;

    // 1. Header & User Info
    cout << "=================================================\n";
    cout << "              FINANCIAL TRACKER APP              \n";
    cout << "=================================================\n";
    
    // Display dynamic info (Name, Wallet, Remainder)
    cout << " User:      " << userName << "\n";
    cout << " Wallet:    " << currentWallet << "\n";
    cout << " Remainder: $" << fixed << setprecision(2) << currentRemainder << "\n"; 
    cout << "-------------------------------------------------\n";

    // 2. Selectable Options
    cout << "1. Wallet List (Switch/View Wallets)\n";
    cout << "2. Transaction History\n";
    cout << "3. Add Transaction (Update)\n";//Recurring and normal Transaction
    cout << "4. Recurring Transaction List\n";
    cout << "5. Save Progress\n";
    cout << "6. Exit (Auto-Save & End)\n";
    cout << "-------------------------------------------------\n";
    cout << "Select option: ";
}
void Draw_Wallet_List();
void Draw_Transaction_History();
void Draw_Add_Transaction();
void Draw_Recurring_Transaction_List();
void Input_Choice(int& choice);
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
int main()
{
    
}