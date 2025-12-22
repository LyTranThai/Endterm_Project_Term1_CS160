#pragma once
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include "Date.h"
#include "Recurring_Transaction.h"
using namespace std;


void WriteString(ofstream &out, const string &s);

// đọc xâu
void ReadString(ifstream &in, string &s);

template <typename T>
void resize1(T** & p, int size, int cap);

template <typename T>
bool Find_By_ID(int& id,T**& list, int& size,T*& pointer);

template <typename T>
bool Find_By_Name(string& name,T**& list, int& size,T*& pointer);

bool compare_string(string& s1, string& s2);  

template <typename T>
int Generate_ID(T** list, int count);

bool check_string(string info, char c);


void Clear_Buffer();

void ClearLines(int numLines);


void OutputDateTable(Date src);
template <typename T>
void Show_Transaction(T**& list, int list_size);

template <typename T>
void Sort_By_Date_Transaction(T**& list, int list_size);

template <typename T>
void Show_Recur_Transaction(T**& list, int list_size);



void print_center(string s,char c, int width);