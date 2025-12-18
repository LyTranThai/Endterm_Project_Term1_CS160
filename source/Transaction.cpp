#include "../header/Transaction.h"
#include "../header/InfoArray.h"
#include "../header/MasterDataFunc.h"

    //Format
    // Date/Month/Year^Type of transaction^Amount^WalletName^Description
bool Transaction_Income::Input_Transaction(string info,IncomeSourceArray array)
{
    stringstream ss(info);
    string segment;
    int length=10;
    string* data=new string[length];
    int i = 0;
    while (getline(ss,segment,'^'))
    {
        if(i>=length)
        {
            resize(data, i, length);
        }
        data[i]=segment;
        i++;
    }
    if(i<7)
    {
        cerr << "Error: Invalid data format -> " << info << endl;
        return false;
    }
    // try {
    //     int count=0;
    //     this->date=InputDate(data[count]);
    //     count+=1;
        
    //     if (i > 3) {
    //         this->type = array[findIncomeSrcIndexById(array,stoi(data[count]))];
    //         count += 1;
    //         this->amount=stoll(data[count]);
            
    //         this->amount = stoll(data[i-1]); // Take the very last element as balance
    //     } else {
    //         this->name = data[1];
    //         this->amount = stoll(data[2]); // CHANGED: stoll for long long
    //     }
    // }
    // catch (const exception& e) {
    //     cerr << "Error: Conversion failed for line -> " << info << endl;
    //     delete[] data;
    //     data=nullptr;
    //     return false;
    // }
    // delete[]data;
    // data=nullptr;
    return true;
    

}
bool Output_Terminal(Transaction_Income);
