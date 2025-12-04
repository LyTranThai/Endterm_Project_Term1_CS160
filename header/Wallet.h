#pragma once
#include <iostream>
#include <sstream>
using namespace std;


struct Amount;


struct Wallet
{
    int ID;
    string name;
    long long remain;
};

void Input_With_Textfile(string filename);
void Output_Save_Textfile(string filename);

//Format
//ID-Name-remain
void Input_Wallet(string info);
