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

void drawMenu(string userName, string currentWallet, double currentRemainder) {
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
int main()
{
    drawMenu("Name", "Wallet", 100000);
}