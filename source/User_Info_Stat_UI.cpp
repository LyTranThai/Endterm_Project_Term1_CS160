#include "../header/User_Info.h"

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
        Clear_Buffer();
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
    bool check = true;
    int startYear, endYear;
    while(true)
    {
    clearScreen();
    cout << "\n=== ANNUAL INCOME/EXPENSE OVERVIEW ===\n";
    if(!check)
    {
        cout<<"[Error] Please enter a valid integer for year!"<<endl;
    }
    cout << "Enter Start Year (e.g., 2023): ";
    check=true;
    if (!Input_Choice(startYear))
        {
            check=false;
            continue;
        }
    Clear_Buffer();
    cout << "Enter End Year (e.g., 2025): ";
    if (!Input_Choice(endYear))
        {
            check=false;
            continue;
        }
    Clear_Buffer();
    break;
    }

    if (startYear > endYear)
    {
        cout<<"Auto Year-Swap"<<endl;
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
    int year;
    bool check = true;
    Clear_Buffer();
    while(true)
    {
    clearScreen();
    cout << "\n=== ANNUAL BREAKDOWN ===\n";
    if(!check)
    {
        cout<<"[Error] Please enter a valid integer for year!"<<endl;
    }
    cout << "Enter Year to analyze: (e.g., 2023): ";
    check=true;
    if (!Input_Choice(year))
        {
            check=false;
            continue;
        }
    Clear_Buffer();
    break;
    }
    

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
        clearScreen();
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
        if (!Input_Choice(choice))
        {
            cout << "\n[!] Invalid input. Please enter a number.\n";
            pause();
            continue;
        }

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

