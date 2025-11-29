#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\Currency.h"



void Input_Currency(string filename,Currency*& Currency_List)

{
    
    ifstream fin;
    int n;

    fin.open(filename);
    fin >> n;
    if(!fin.is_open())
    {
        cerr<<"Can not open file"<<filename<<endl;

    }
    if(Currency_List!=nullptr)
    {
        delete[]Currency_List;
    }
    Currency_List= new Currency[n];
    string info;


    int i=0;
    while (i<n && getline(fin,info))

    {
        stringstream ss(info);
        ss>>Currency_List[i].unit>>Currency_List[i].ratio;
        i++;
    }
    fin.close();
    
}