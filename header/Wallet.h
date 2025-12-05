#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;


struct Amount;


struct Wallet
{
    int ID;
    string name;
    long long remain;

    bool Input_Wallet(string info);
    void Output_Terminal();
};

bool Input_With_Textfile(string filename);
void Output_Save_Textfile(string filename);

//Format
//ID-Name-remain

