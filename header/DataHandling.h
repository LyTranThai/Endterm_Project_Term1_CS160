#pragma once
#include <iostream>
#include <fstream>
#include <limits>
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