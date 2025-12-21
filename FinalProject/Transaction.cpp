#include "../header/Transaction.h"
#include "../header/InfoArray.h"
#include "../header/MasterDataFunc.h"


void WriteString(ofstream &out, const string &s)
{
    size_t len = s.size();
    out.write((char *)&len, sizeof(len)); // xâu length
    if (len > 0)
    {
        out.write(s.c_str(), len); // print xau
    }
}
void ReadString(ifstream &in, string &s)
{
    size_t len = 0;
    in.read((char *)&len, sizeof(len));
    if (in.gcount() != sizeof(len))
        return;

    if (len > 0)
    {
        s.resize(len);
        in.read(&s[0], len);
    }
    else
    {
        s = "";
    }
}
// Date date;
// ExpenseCategory type;
// long long amount;
// Wallet wallet;
// string description;
// Date/strin
// void Transaction_Expense::SaveToBinary(ofstream& out,string filename)
// {

//     out.write(reinterpret_cast<char*> (&this->date), sizeof(Date));
//     out.write(reinterpret_cast<char*> (&this->type->id),sizeof(int));
//     //No need to write name
//     out.write(reinterpret_cast<char*> (&this->wallet->id),sizeof(int));
//     WriteString(out,this->description);

// }
// void Transaction_Expense::LoadFromBinary(ifstream& input,string filename)
// {
//     input.read(reinterpret_cast<char*>(&this->date), sizeof(Date));
//     input.read(reinterpret_cast<char*> (&this->type->id),sizeof(int));
//     //No need to write name
//     input.read(reinterpret_cast<char*> (&this->wallet->id),sizeof(int));
//     ReadString(input,this->description);

// }


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
