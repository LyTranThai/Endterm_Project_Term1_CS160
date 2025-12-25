#include "../header/InfoArray.h"
#include <fstream>
#include <sstream>
#include "../header/Wallet.h"

template <typename T>
void resize(T *&array, int &size, int &capcity)
{
    while (size >= capcity)
    {

        capcity *= 2;
        T *New_Array = new T[capcity]; // I want the type here to be the same as array
        for (int i = 0; i < size; i++)
        {
            New_Array[i] = array[i];
        }
        delete[] array;
        array = New_Array;
    }
}


Wallet& Wallet::operator=(const Wallet &src)
{

    if (this == &src)
        return *this;


    this->id = src.id;
    this->name = src.name;
    this->remain = src.remain;
    this->inCount = src.inCount;
    this->inCap = src.inCap;
    this->expCount=src.expCount;
    this->expCap=src.expCap;
    this->incomes = new Transaction_Income*[src.inCap];
    this->expenses = new Transaction_Expense*[src.expCap];
    for(int i = 0; i < src.inCount; i++) 
    {
        this->incomes[i]=src.incomes[i];
    }
    for(int i=0; i< src.expCount; i++)
    {
        this->expenses[i]=src.expenses[i];
    }
    return *this;
}

template <typename T>
void add_element(T *&array, int &size, int &capcity, T element)
{
    resize(array, size, capcity);
    array[size] = element;
    size += 1;
}

bool Wallet::Input_Wallet(string info)
{
    int length = 10;
    string *data = new string[length];
    stringstream ss(info);
    int i = 0;
    string segment;
    while (getline(ss,segment,'^'))
    {
        if (i >= length)
        {
            resize(data, i, length);
        }
        data[i] = segment;
        i++;
    }
    if (i < 3)
    {
        cerr << "Error: Invalid data format -> " << info << endl;
        return false;
    }
    try
    { /*  */
        this->id = stoi(data[0]);

        if (i > 3)
        {
            this->name = data[1];
            for (int j = 2; j < i - 1; j++)
            {
                this->name += "-" + data[j];
            }
            this->remain = stoll(data[i - 1]);
        }
        else
        {
            this->name = data[1];
            this->remain = stoll(data[2]);
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: Conversion failed for line -> " << info << endl;
        delete[] data;
        data = nullptr;
        return false;
    }
    delete[] data;
    data = nullptr;
    return true;
}
void Wallet::Output_Terminal()
{
    cout << setw(5) << right << this->id;
    cout << setw(5) << right << this->name;
    cout << setw(5) << right << this->remain << endl;
}




void Wallet::Wallet_resize()
{
    resize1(this->expenses, this->expCount, this->expCap);
    resize1(this->incomes,this->inCount,this->inCap);
}

void Wallet::Wallet_resize_no_copy()
{
    while (this->inCount>=inCap)
    {
        inCap*=2;
    }
    while(this->expCount>=expCap)
    {
        expCap*=2;
    }

    delete[]incomes;
    incomes= new Transaction_Income*[inCap];
    delete[]expenses;
    expenses = new Transaction_Expense*[expCap];
    
}

// Thêm
//
//
//
//
//
//
//
//
//
//
// Vì cnay của wallet, ném qua info kh biết nên tìm ở đâu, nên t để dây tạm


