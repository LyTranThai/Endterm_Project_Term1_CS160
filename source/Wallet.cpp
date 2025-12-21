#include "InfoArray.h"
#include <fstream>
#include <sstream>
#include "Wallet.h"

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

template <typename T>
void add_element(T *&array, int &size, int &capcity, T element)
{
    resize(array, size, capcity);
    array[size] = element;
    size += 1;
}

bool Wallet::Input_Wallet(string info)
{
    string info;
    cout<<"Type In your Wallet Name (Does not contain '^'): ";
    getline(cin,info);
    if(check_string(info,'^'))
    {
        cout<<"\nInvalid Name\n"<<endl;
        cout<<"Press any key to retry..."<<endl;
        cin.get();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    this->name=info;
    cout<<"Type In your Wallet ID (Does not contain '^'): ";
    getline(cin,info);
    if(check_string(info,'^'))
    {
        cout<<"\nInvalid Name\n"<<endl;
        cout<<"Press any key to retry..."<<endl;
        cin.get();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    this->name=id;
    this->remain=0;
    cout<<"Your wallet created "<<this->name<<" ID: "<<this->id<<endl;
    return true;

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

bool WalletArray::Input_With_Textfile(string filename)
{
    ifstream fin;
    fin.open(filename);
    if (!fin.is_open())
    {
        cerr << "Error Opening " << filename << endl;
        return false;
    }

    string info;
    while (getline(fin, info))
    {
        if (info.empty())
            continue; //

        Wallet w;
        if (!w.Input_Wallet(info))
        {
            cerr << "Warning: skipping invalid line -> " << info << endl;
            continue;
        }

        add_element(this->data, this->size, this->capacity, w);
    }

    fin.close();
    return true;
}
bool WalletArray::Output_Save_Textfile(string filename)
{
    ofstream fout;
    if (!fout.is_open())
    {
        cerr << "Error Opening " << filename << endl;
        return false;
    }
    for (int i = 0; i < this->size; i++)
    {
        fout << this->data[i].id << "-" << this->data[i].name << "-" << this->data[i].remain << endl;
    }
    return true;
    fout.close();
}


void Wallet::Wallet_resize()
{
    resize1(this->expenses, this->expCount, this->expCap);
    resize1(this->incomes,this->inCount,this->inCap);
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


