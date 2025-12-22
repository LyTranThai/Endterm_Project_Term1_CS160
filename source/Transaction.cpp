#include "../header/Transaction.h"
#include "../header/InfoArray.h"
#include "../header/MasterDataFunc.h"



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

bool Output_Terminal(Transaction_Income);
