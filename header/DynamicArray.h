#include "MasterData.h"

struct ExpenseCategoryArray
{
    ExpenseCategory *data;
    int size;
    int capacity;
};

struct IncomeSourceArray
{
    IncomeSource *data;
    int size;
    int capacity;
};

struct WalletArray
{
    Wallet *data;
    int size;
    int capacity;
};

const int INITIAL_CAPACITY = 10;
template <typename T>
void resize(T*& array, int& size,int& capcity)
{
    while (size>=capcity)
    {
        
        capcity *= 2;
        void*New_Array=array;
        New_Array=new T[capcity];//I want the type here to be the same as array
        for(int i=0; i<size; i++)
        {
            New_Array[i]=array[i];
        }
        delete[]array;
        array=New_Array;
    }

}

template <typename T>
void add_element(T*& array, int& size,int& capcity, T element)
{
    resize(T*& array, int& size,int& capcity);
    array[size]= element;
    size+=1;
}