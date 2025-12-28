
#include "../header/DataHandling.h"
#include "../header/transaction.h"           // Added: Needed for Transaction struct details
#include "../header/Recurring_Transaction.h" // Added: Needed for Recurring struct details
#include "../header/Wallet.h"

void clearScreen()
{
// If you are on Windows, use "cls". If on Mac/Linux, use "clear"
#ifdef _WIN32
    system("cls");
#endif
}

// Wait for the user to press something
void pause()
{
    cout << "\nPress Enter to continue...";
    // This line clears any leftover "Enter" keys in the keyboard buffer
    // This line waits for a NEW "Enter" key press
    std::cin.get();
}

bool Input_Choice(int &choice)
{
    string input;
    std::getline(std::cin, input);

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

string Date_to_string(Date d)
{
    string out="";
    out += to_string(d.day) + "/" + to_string(d.month)+"/" +to_string(d.year);
    return out;
}

void WriteString(ofstream &out, const string &s)
{
    size_t len = s.size();
    out.write((char *)&len, sizeof(len)); // xâu length
    if (len > 0)
    {
        out.write(s.c_str(), len); // print xau
    }
}

// đọc xâu
void ReadString(ifstream &in, string &s)
{
    size_t len = 0;
    in.read((char *)&len, sizeof(len));
    if (in.gcount() != sizeof(len))
        return;

    if (len > 0)
    {
        s.resize(len);
        in.read(&s[0], len);
    }
    else
    {
        s = "";
    }
}

template <typename T>
void Tresize1(T **&p, int size, int &cap)
{
    if(size>=cap)
    {
        int save=cap;
    while (size >= cap)
    {
        cap *= 2;
    }

    T **dummy = p;
    p = new T *[cap];

    for (int i = 0; i < save; i++)
    {
        p[i] = dummy[i];
    }

    delete[] dummy;
    for (int i = save; i < cap; i++)
    {
        p[i] = NULL;
    }
    }
}

void resize1(Wallet **&p, int size, int &cap)
{
    Tresize1(p, size, cap);
}
void resize1(IncomeSource **&p, int size, int &cap)
{
    Tresize1(p, size, cap);
}
void resize1(ExpenseCategory **&p, int size, int &cap)
{
    Tresize1(p, size, cap);
}
void resize1(Transaction_Income **&p, int size, int &cap)
{
    Tresize1(p, size, cap);
}
void resize1(Transaction_Expense **&p, int size, int &cap)
{
    Tresize1(p, size, cap);
}
void resize1(Recurring_Transaction_Income **&p, int size, int &cap)
{
    Tresize1(p, size, cap);
}
void resize1(Recurring_Transaction_Expense **&p, int size, int &cap)
{
    Tresize1(p, size, cap);
}

template <typename T>
bool TFind_By_ID(int &id, T **&list, int &size, T *&pointer)
{
    bool check = false;
    for (int i = 0; i < size; i++)
    {
        if (list[i]->id == id)
        {
            pointer = list[i];
            check = true;
            break;
        }
    }
    if (!check)
    {
        pointer = list[0];
    }
    return check;
}
bool Find_By_ID(int id, Wallet **&list, int &size, Wallet *&pointer)
{
    return TFind_By_ID(id, list, size, pointer);
}
bool Find_By_ID(int id, IncomeSource **&list, int &size, IncomeSource *&pointer)
{
    return TFind_By_ID(id, list, size, pointer);
}
bool Find_By_ID(int id, ExpenseCategory **&list, int &size, ExpenseCategory *&pointer)
{
    return TFind_By_ID(id, list, size, pointer);
}
bool Find_By_ID(int id, Recurring_Transaction_Income **&list, int &size, Recurring_Transaction_Income *&pointer)
{
    return TFind_By_ID(id, list, size, pointer);
}
bool Find_By_ID(int id, Recurring_Transaction_Expense **&list, int &size, Recurring_Transaction_Expense *&pointer)
{
    return TFind_By_ID(id, list, size, pointer);
}

template <typename T>
bool TFind_By_Name(string &name, T **&list, int &size, T *&pointer)
{
    bool check = false;
    for (int i = 0; i < size; i++)
    {
        if (compare_string(name, list[i]->name))
        {
            pointer = list[i];
            check = true;
            break;
        }
    }
    if (!check)
    {
        pointer = list[0];
    }
    return check;
}

bool Find_By_Name(string &name, Wallet **&list, int &size, Wallet *&pointer)
{
    return TFind_By_Name(name, list, size, pointer);
}
bool Find_By_Name(string &name, IncomeSource **&list, int &size, IncomeSource *&pointer)
{
    return TFind_By_Name(name, list, size, pointer);
}
bool Find_By_Name(string &name, ExpenseCategory **&list, int &size, ExpenseCategory *&pointer)
{
    return TFind_By_Name(name, list, size, pointer);
}

bool compare_string(string &s1, string &s2)
{
    if (s1.size() != s2.size())
    {
        return false;
    }
    for (int i = 0; i < s1.size(); i++)
    {
        if (s1[i] != s2[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
int TGenerate_ID(T **list, int count)
{
    if (count == 0)
        return 1; // Start at 1 if list is empty

    int max_id = 0;
    for (int i = 0; i < count; i++)
    {
        if (list[i]->id > max_id)
        {
            max_id = list[i]->id;
        }
    }
    return max_id + 1;
}

int Generate_ID(Wallet **list, int count)
{
    return TGenerate_ID(list, count);
}
int Generate_ID(IncomeSource **list, int count)
{
    return TGenerate_ID(list, count);
}
int Generate_ID(ExpenseCategory **list, int count)
{
    return TGenerate_ID(list, count);
}
int Generate_ID(Recurring_Transaction_Income **list, int count)
{
    return TGenerate_ID(list, count);
}
int Generate_ID(Recurring_Transaction_Expense **list, int count)
{
    return TGenerate_ID(list, count);
}

bool check_string(string info, char c)
{
    for (int i = 0; i < info.size(); i++)
    {
        if (info[i] == c)
        {
            return true;
        }
    }
    return false;
}

void Clear_Buffer()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void ClearLines(int numLines)
{
    for (int i = 0; i < numLines; i++)
    {
        // \033[A moves cursor up 1 line
        // \033[2K clears the entire line
        cout << "\033[A" << "\033[2K";
    }
}

void OutputDateTable(Date src)
{
    stringstream ss;
    // Force 2 digits for day/month and 4 for year (e.g., 05/01/2024)
    ss << setfill('0') << setw(2) << src.day << "/"
       << setw(2) << src.month << "/"
       << setw(4) << src.year;

    // Print the string with padding to fill 15 characters
    cout << left << setfill(' ') << setw(15) << ss.str();
}

// Helper to wrap text nicely
// content: The text to print
// width: The maximum width of the text block
// indent: How many spaces to indent subsequent lines
void PrintWrapped(string content, int width, int indent)
{
    if (content.empty())
        return;

    stringstream ss(content);
    string word;
    int currentLen = 0;

    while (ss >> word)
    {
        // Check if adding this word exceeds the width
        // (+1 is for the space we would add)
        if (currentLen + word.length() + 1 > width)
        {
            // Wrap to new line
            cout << endl;
            // Print indentation spaces
            cout << string(indent, ' ');
            currentLen = 0;
        }

        // Add space before word (unless it's the start of a new line)
        if (currentLen > 0)
        {
            cout << " ";
            currentLen++;
        }

        cout << word;
        currentLen += word.length();
    }
}

template <typename T>
void TShow_Transaction(T **&list, int list_size,int n)
{
    const int wDate = 14;
    const int wCat = 22;
    const int wWal = 18;
    const int wAmt = 15;
    // Define the total width of the "Card"
    const int CARD_WIDTH = 60;
    // OutputDateTable prints 15 chars. Remaining space for Amount = 90 - 15 = 75.
    const int AMT_WIDTH = CARD_WIDTH - 15;

    if (list_size == 0)
    {
        cout << "\n";
        cout << string(CARD_WIDTH, '-') << "\n";
        cout << "No transaction yet!" << endl;
        cout << string(CARD_WIDTH, '-') << "\n";
        return;
    }

    cout << "\n";

    for (int i = list_size-n; i < list_size; i++)
    {
        if(i<0) continue;
        // 1. Top Border of the "Card"
        cout << string(CARD_WIDTH, '-') << "\n";

        // 2. Row 1: Date [LEFT] .............................. Amount [RIGHT]
        // OutputDateTable handles the first 15 chars (e.g., "01/01/2024   ")
        OutputDateTable(list[i]->date);
        // Push Amount to the far right
        cout << right << setw(AMT_WIDTH) << list[i]->amount << endl;

        // 3. Row 2: Category / Type Name
        string typeName = (list[i]->type) ? list[i]->type->name : "Unknown Source";
        cout << left << setw(CARD_WIDTH) << typeName << endl;

        // 4. Row 3: Wallet Name
        string walletName = (list[i]->wallet) ? list[i]->wallet->name : "Unknown Wallet";
        cout << left << "Via: " << walletName << endl;

        // 5. Row 4: Description (Only if it exists, or placeholder)
        if (!list[i]->description.empty())
        {
            cout<<"Note: ";
            PrintWrapped(list[i]->description, CARD_WIDTH - 6, 0);
            cout << endl;
        }
        else
        {
            cout << left << "Note: (No description)" << endl;
        }
    }
    // Bottom Border
    cout << string(CARD_WIDTH, '-') << "\n";
}

void Show_Transaction(Transaction_Income **&list, int list_size)
{
    TShow_Transaction(list, list_size,10);
}
void Show_Transaction(Transaction_Expense **&list, int list_size)
{
    TShow_Transaction(list, list_size,10);
}
void Show_All_Transaction(Transaction_Income **&list, int list_size)
{
    TShow_Transaction(list, list_size, list_size);
}
void Show_All_Transaction(Transaction_Expense **&list, int list_size)
{
    TShow_Transaction(list, list_size,list_size);
}
/*
------------------------------------------------------------------------------------------
Date          Amount
Type
Description
------------------------------------------------------------------------------------------
Date          Amount
Type
Description
------------------------------------------------------------------------------------------
Date          Amount
Type
Description
------------------------------------------------------------------------------------------

*/

template <typename T>
void TShow_Recur_Transaction(T **&list, int list_size)
{
    const int wDate = 14;
    const int wCat = 22;
    const int wWal = 18;
    const int wAmt = 15;
    // Define the total width of the "Card"
    const int CARD_WIDTH = 60;
    // OutputDateTable prints 15 chars. Remaining space for Amount = 90 - 15 = 75.
    const int AMT_WIDTH = CARD_WIDTH - 2 * wDate - 5;

    if (list_size == 0)
    {
        cout << "\n";
        cout << string(CARD_WIDTH, '-') << "\n";
        cout << "No transaction yet!" << endl;
        cout << string(CARD_WIDTH, '-') << "\n";
        return;
    }

    cout << "\n";

    for (int i = 0; i < list_size; i++)
    {
        // 1. Top Border of the "Card"
        cout << string(CARD_WIDTH, '-') << "\n";
        //print ID
        cout<<"ID: "<< list[i]->id<<endl;
        // 2. Row 1: Date [LEFT] .............................. Amount [RIGHT]
        // OutputDateTable handles the first 15 chars (e.g., "01/01/2024   ")
        OutputDateTable(list[i]->start);
        cout << " to ";
        OutputDateTable(list[i]->end);
        // Push Amount to the far right
        cout << right << setw(AMT_WIDTH) << list[i]->amount << endl;

        // 3. Row 2: Category / Type Name
        string typeName = (list[i]->type) ? list[i]->type->name : "Unknown Source";
        cout << left << setw(CARD_WIDTH) << typeName << endl;

        // 4. Row 3: Wallet Name
        string walletName = (list[i]->wallet) ? list[i]->wallet->name : "Unknown Wallet";
        cout << left << "Via: " << walletName << endl;

        // 5. Row 4: Description (Only if it exists, or placeholder)
        if (!list[i]->description.empty())
        {
            cout<<"Note: ";
            PrintWrapped(list[i]->description, CARD_WIDTH - 6, 6);
            cout << endl;
        }
        else
        {
            cout << left << "Note: (No description)" << endl;
        }
    }
    // Bottom Border
    cout << string(CARD_WIDTH, '-') << "\n";
}

void Show_Recur_Transaction(Recurring_Transaction_Income **&list, int list_size)
{
    TShow_Recur_Transaction(list, list_size);
}
void Show_Recur_Transaction(Recurring_Transaction_Expense **&list, int list_size)
{
    TShow_Recur_Transaction(list, list_size);
}

template <typename T>
void TSort_By_Date_Transaction(T **&list, int list_size)
{
    for (int i = list_size - 1; i >= 0; i--)
    {
        int max_idx = i; // Assume current is the intended one
        for (int j = i - 1; j >= 0; j--)
        {
            // Assuming result '2' means list[min_idx] > list[j] (i.e., we want ascending order)
            // If you want Descending (newest first), reverse the logic
            if (compare_Date(list[j]->date, list[max_idx]->date) == 2)
            {
                max_idx = j; // Just update the index, don't swap yet
            }
        }

        // Swap only once per outer loop
        if (max_idx != i)
        {
            T *save = list[i];
            list[i] = list[max_idx];
            list[max_idx] = save;
        }
    }
}

void Sort_By_Date_Transaction(Transaction_Income **&list, int list_size)
{
    TSort_By_Date_Transaction(list, list_size);
}
void Sort_By_Date_Transaction(Transaction_Expense **&list, int list_size)
{
    TSort_By_Date_Transaction(list, list_size);
}

// Check if this recur trans have been added given the time

void print_center(string s, char c, int width)
{
    cout << string((width - s.length()) / 2, c) << s << string((width - s.length()) / 2, c);
}