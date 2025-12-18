#pragma once
#include <iostream>
#include <fstream>
using namespace std;


void WriteString(ofstream &out, const string &s);

// đọc xâu
void ReadString(ifstream &in, string &s);

template <typename T>
void resize1(T** & p, int size, int cap);