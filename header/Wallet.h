#pragma once
#include <iostream>
using namespace std;
#include "Amount.h"

struct Amount;


struct Wallet
{
    int ID;
    string name;
    Amount remain;
};

void Input_With_Textfile(string filename);
void Output_Save_Textfile(string filename);
