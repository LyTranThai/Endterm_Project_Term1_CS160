#include "../header/Wallet.h"


bool Wallet::Input_Wallet(string info)
{
    int length=10;
    string* data=new string[length];
    stringstream ss(info);
    int i=0;
    while (getline(ss,data[i],'-'))
    {
        i++;
        if(i>)
    }
    if(i<3)
    {
        cerr << "Error: Invalid data format -> " << info << endl;
        return false;
    }

    this->ID=stoi(data[0]);
    this->name=data[1];
    this->remain=stoll(data[2]);
}
void Wallet::Output_Terminal()
{
    cout<<setw(5)<<right<<this->ID;
    cout<<setw(5)<<right<<this->name;
    cout<<setw(5)<<right<<this->remain<<endl;   
}