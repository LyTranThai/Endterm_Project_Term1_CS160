#include <iostream>
#include "User_Info.h"

using namespace std;
// MUST RUN TO INPUT CURRENCY DATA
//  int main()
//  {
//  //Create Currency List
//      Currency * Currency_Type=new Currency[3];
//      Input_Currency("currency",Currency_Type);
//      delete[]Currency_Type;
//      return 0;
//  }

#include <vector>
#include <string>
#include <iomanip> // For formatting tables
#include <fstream> // For File I/O
#include <limits>  // For input cleaning

string filename = "user_data.bin";

Transaction_Type type[100];
int number_of_type = 0;

using namespace std;
bool Input_Choice(int &choice)
{
    string input;
    getline(cin, input);

    try
    {
        choice = stoi(input);
        return true; // Try to convert string to int
    }
    catch (...)
    {
        return false; // reset
    }
}

// Clear screen
void clearScreen()
{
// If you are on Windows, use "cls". If on Mac/Linux, use "clear"
#ifdef _WIN32
    system("cls");
#else system("clear");
#endif
}

void Clear_Buffer()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
// Wait for the user to press something
void pause()
{
    cout << "\nPress Enter to continue...";
    // This line clears any leftover "Enter" keys in the keyboard buffer
    // This line waits for a NEW "Enter" key press
    cin.get();
}

void drawMenu(User_Info &user) // ifstream& fin
{
    string userName = "UserName";
    string currentWallet = "DefaultWallet";
    double currentRemainder = 10000;

    long long totalBalance = 0;
    for (int i = 0; i < user.wallet_count; i++)
    {
        totalBalance += user.Wallet_List[i]->remain;
    }

    // 1. Header & User Info
    cout << "=================================================\n";
    cout << "              FINANCIAL TRACKER APP              \n";
    cout << "=================================================\n";

    if (user.wallet_count > 0)
        cout << " Wallet:    " << user.Wallet_List[0]->name << " (Main)\n";
    else
        cout << " Wallet:    No Wallet\n";

    // Display dynamic info (Name, Wallet, Remainder)
    cout << " User:      " << userName << "\n";
    cout << " Wallet:    " << currentWallet << "\n";
    cout << " Remainder: $" << fixed << setprecision(2) << currentRemainder << "\n";
    cout << "-------------------------------------------------\n";

    // 2. Selectable Options
    cout << "1. Wallet List (Switch/View Wallets)\n";
    cout << "2. Transaction History\n";
    cout << "3. Add Transaction (Update)\n"; // Recurring and normal Transaction
    cout << "4. Recurring Transaction List\n";
    cout << "5. Save Progress\n";
    cout << "6. Exit (Auto-Save & End)\n";
    cout << "-------------------------------------------------\n";
    cout << "Select option: ";
}

void Draw_Wallet_List(); // 1.Change Wallet 2. back
void Draw_Transaction_History();
void Draw_Add_Transaction();
void Draw_Recurring_Transaction_List();
bool Input_Choice(int &choice);
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
void RunApplication_Navigation(User_Info &user)
{
    while (true)
    {
        int choice;
        clearScreen();
        drawMenu(user);
        if (!Input_Choice(choice))
        {
            cout << "\n[!] Invalid input. Please enter a number.\n";
            pause();
            continue;
        }
        switch (choice)
        {
        case 1:
            clearScreen();
            Draw_Wallet_List();
            break;
        case 2:
            clearScreen();
            Draw_Transaction_History();
            break;
        case 3:
            clearScreen();
            Draw_Add_Transaction();
            break;
        case 4:
            clearScreen();
            Draw_Recurring_Transaction_List();
            break;
        case 5:
        {
            ofstream outFile(filename, ios::binary);
            if (outFile.is_open())
            {
                user.SaveToBinary(outFile, filename);
                outFile.close();
                cout << "\n[Success] Data saved to " << filename << "\n";
            }
            else
            {
                cout << "\n[Error] Could not open file to save!\n";
            }
            pause();
        }
            cout << "\nSaving progress... (Functionality to be implemented)\n";
            pause();
            break;
        case 6:
        {
            ofstream outFile(filename, ios::binary);
            if (outFile.is_open())
            {
                user.SaveToBinary(outFile, filename);
                outFile.close();
                cout << "\nData saved. Exiting application. Goodbye!\n";
            }
            return;
        }
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

    User_Info user;

    cout << endl;
    cout << "=================================================\n";
    cout << "              FINANCIAL TRACKER APP              \n";
    cout << "=================================================\n";
    cout << "Type in your name" << endl;
    string name;
    cin >> name;
    User_Info user;

    ifstream inFile(filename, ios::binary);
    if (inFile.is_open())
    {
        cout << "Found existing data. Loading...\n";
        // Lưu ý: User_Info cần logic init mảng trước khi load (đã có trong constructor)
        user.LoadFromBinary(inFile, filename);
        inFile.close();
        cout << "Welcome back, " << user.name << "!\n";
        pause();
    }
    else
    {
        cout << "No data found. Creating new user.\n";
        cout << "Type in your name: ";
        getline(cin, user.name);

        // Tạo ví mặc định để user không bị lỗi khi mới vào
        user.Add_Wallet(); // Yêu cầu người dùng tạo ví đầu tiên ngay lập tức
    }

    RunApplication_Navigation(user);
    return 0;
}