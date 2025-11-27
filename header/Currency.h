#pragma once
#include <iostream>
#include<fstream>
#include <sstream>
using namespace std;




struct Currency
{
    string unit;
    double ratio;
};

void Input_Currency(string filename);

