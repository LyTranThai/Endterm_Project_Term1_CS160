#include <iostream>
#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Currency.h"
#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Date.h"
#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Transaction_Type.h"
#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Transaction.h"
#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Wallet.h"
#include "Currency.cpp"
using namespace std;

int main()
{
//Create Currency List
    Currency * Currency_Type=new Currency[3];
    Input_Currency("currency",Currency_Type);
    delete[]Currency_Type;



    return 0;

}

