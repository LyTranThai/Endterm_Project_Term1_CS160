#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Currency.h"

void Input_Currency(string filename,Currency Currency_List[])
{
    
    ifstream fin;
    int n;

    fin.open(filename);
        fin >> n;
    Currency* Currency_List= new Currency[n];
    string info;
    int i=0;
    while (getline(fin,info))
    {
        stringstream ss(info);

    }
    
}