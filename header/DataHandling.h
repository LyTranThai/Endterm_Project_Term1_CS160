#pragma once
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include "Date.h"
using namespace std;

// --- FORWARD DECLARATIONS (Crucial Fix) ---
// This tells the compiler these structs exist without including their full files
struct Transaction_Income;
struct Transaction_Expense;
struct Recurring_Transaction_Income;
struct Recurring_Transaction_Expense;
struct Wallet;
struct ExpenseCategory;
struct IncomeSource;

void clearScreen();
// Wait for the user to press something
void pause();
bool Input_Choice(int &choice);


string Date_to_string(Date d);

void WriteString(ofstream &out, const string &s);
void ReadString(ifstream &in, string &s);

void resize1(Wallet **&p, int size, int &cap);
void resize1(IncomeSource **&p, int size, int &cap);
void resize1(ExpenseCategory **&p, int size, int &cap);
void resize1(Transaction_Income **&p, int size, int &cap);
void resize1(Transaction_Expense **&p, int size, int &cap);
void resize1(Recurring_Transaction_Income **&p, int size, int &cap);
void resize1(Recurring_Transaction_Expense **&p, int size, int &cap);

bool Find_By_ID(int id, Wallet **&list, int &size, Wallet *&pointer);
bool Find_By_ID(int id, IncomeSource **&list, int &size, IncomeSource *&pointer);
bool Find_By_ID(int id, ExpenseCategory **&list, int &size, ExpenseCategory *&pointer);
bool Find_By_ID(int id, Recurring_Transaction_Income **&list, int &size, Recurring_Transaction_Income *&pointer);
bool Find_By_ID(int id, Recurring_Transaction_Expense **&list, int &size, Recurring_Transaction_Expense *&pointer);

bool Find_By_Name(string &name, Wallet **&list, int &size, Wallet *&pointer);
bool Find_By_Name(string &name, IncomeSource **&list, int &size, IncomeSource *&pointer);
bool Find_By_Name(string &name, ExpenseCategory **&list, int &size, ExpenseCategory *&pointer);

bool compare_string(string &s1, string &s2);

int Generate_ID(Wallet **list, int count);
int Generate_ID(IncomeSource **list, int count);
int Generate_ID(ExpenseCategory **list, int count);
int Generate_ID(Recurring_Transaction_Income **list, int count);
int Generate_ID(Recurring_Transaction_Expense **list, int count);

bool check_string(string info, char c);

void Clear_Buffer();

void ClearLines(int numLines);

void OutputDateTable(Date src);

void Show_Transaction(Transaction_Income **&list, int list_size);
void Show_Transaction(Transaction_Expense **&list, int list_size);

void Sort_By_Date_Transaction(Transaction_Income **&list, int list_size);
void Sort_By_Date_Transaction(Transaction_Expense **&list, int list_size);

void Show_Recur_Transaction(Recurring_Transaction_Income **&list, int list_size);
void Show_Recur_Transaction(Recurring_Transaction_Expense **&list, int list_size);

void print_center(string s, char c, int width);