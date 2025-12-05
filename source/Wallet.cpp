#include "../header/Wallet.h"
#include "../header/InfoArray.h"
#include <fstream>

bool Wallet::Input_Wallet(string info)
{
    int length=10;
    string* data=new string[length];
    stringstream ss(info);
    int i=0;
    string segment;
    while (getline(ss,segment,'-'))
    {
        if(i>=length)
        {
            resize(data, i, length);
        }
        data[i]=segment;
        i++;
        
    }
    if(i<3)
    {
        cerr << "Error: Invalid data format -> " << info << endl;
        return false;
    }
    try {
        this->ID = stoi(data[0]);
        
        if (i > 3) {
            this->name = data[1];
            for(int j = 2; j < i - 1; j++) {
                this->name += "-" + data[j];
            }
            this->remain = stoll(data[i-1]); // Take the very last element as balance
        } else {
            this->name = data[1];
            this->remain = stoll(data[2]); // CHANGED: stoll for long long
        }
    }
    catch (const exception& e) {
        cerr << "Error: Conversion failed for line -> " << info << endl;
        delete[] data;
        data=nullptr;
        return false;
    }
    delete[]data;
    data=nullptr;
    return true;
}
void Wallet::Output_Terminal()
{
    cout<<setw(5)<<right<<this->ID;
    cout<<setw(5)<<right<<this->name;
    cout<<setw(5)<<right<<this->remain<<endl;   
}

bool WalletArray::Input_With_Textfile(string filename)
{
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open())
    {
        cerr<<"Error Opening "<<filename<<endl;
        return false;
    }
    else
    {
        string info;
        while(getline(fin,info,'\n'))
        {
            resize(this->data, this->size, this->capacity);
            this->data[size-1].Input_Wallet(info);
        }
        return true;
    }
}
bool WalletArray::Output_Save_Textfile(string filename)
{
    ofstream fout;
    if(!fout.is_open())
    {
        cerr<<"Error Opening "<<filename<<endl;
        return false;
    }
    else
    {
        for(int i=0; i<this->size; i++)
        {
            fout<<this->data[i].ID<<"-"<<this->data[i].name<<"-"<<this->data[i].remain<<endl;
        }
        return true;
    }
}


template <typename T>
void resize(T*& array, int& size,int& capcity)
{
    while (size>=capcity)
    {
        
        capcity *= 2;
        T*New_Array=array;
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
    resize(array, size, capcity);
    array[size]= element;
    size+=1;
}