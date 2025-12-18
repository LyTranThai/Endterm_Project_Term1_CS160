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
bool check_string(string info, char c)
{
    for(int i=0; i<info.size(); i++)
    {
        if(info[i]==c)
        {
            return true;
        }
    }
    return false;
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
void WriteString(ofstream &out, const string &s)
{
    size_t len = s.size();
    out.write((char *)&len, sizeof(len)); // xâu length
    if (len > 0)
    {
        out.write(s.c_str(), len); // print xau
    }
}

// đọc xâu
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

void Wallet::SaveToBinary(string filename)
{
    ofstream fout(filename, ios::binary | ios::trunc);

    if (!fout.is_open())
    {
        cout << "Loi: Khong the mo file de ghi: " << filename << endl;
        return;
    }
    // ID
    fout.write((char *)&this->id, sizeof(int));

    // name
    WriteString(fout, this->name);

    // bà lăng (balance)
    fout.write((char *)&this->remain, sizeof(long long));

    fout.write((char *)&this->inCount, sizeof(int)); // số inc

    for (int i = 0; i < this->inCount; i++)
    {
        Transaction_Income &item = this->incomes[i];

        // date
        fout.write((char *)&item.date, sizeof(Date));
        // id
        fout.write((char *)&item.type.id, sizeof(int));
        // name
        WriteString(fout, item.type.name);
        // Amount
        fout.write((char *)&item.amount, sizeof(long long));
        //  Desc
        WriteString(fout, item.description);
    }

    fout.write((char *)&this->expCount, sizeof(int));

    for (int i = 0; i < this->expCount; i++)
    {
        Transaction_Expense &item = this->expenses[i];

        fout.write((char *)&item.date, sizeof(Date));

        fout.write((char *)&item.type.id, sizeof(int));

        WriteString(fout, item.type.name);

        fout.write((char *)&item.amount, sizeof(long long));

        WriteString(fout, item.description);
    }

    fout.close();
    cout << "Da luu Wallet ID " << this->id << " vao file " << filename << endl;
}

void Wallet::LoadFromBinary(string filename)
{
    ifstream fin(filename, ios::binary);

    if (!fin.is_open())
    {
        cout << "File khong ton tai hoac loi: " << filename << endl;
        return;
    }

    // reset
    this->inCount = 0;
    this->expCount = 0;

    // read wallet
    fin.read((char *)&this->id, sizeof(int));
    ReadString(fin, this->name);
    fin.read((char *)&this->remain, sizeof(long long));

    // inc read
    int tempInCount = 0;
    fin.read((char *)&tempInCount, sizeof(int));

    for (int i = 0; i < tempInCount; i++)
    {
        Transaction_Income item;

        // Date
        fin.read((char *)&item.date, sizeof(Date));
        //  ID
        fin.read((char *)&item.type.id, sizeof(int));
        //  Name
        ReadString(fin, item.type.name);
        // Amount
        fin.read((char *)&item.amount, sizeof(long long));
        //  Descript
        ReadString(fin, item.description);

        add_element(this->incomes, this->inCount, this->inCap, item);
    }

    // Exp đọc
    int tempExpCount = 0;
    fin.read((char *)&tempExpCount, sizeof(int));

    for (int i = 0; i < tempExpCount; i++)
    {
        Transaction_Expense item;

        fin.read((char *)&item.date, sizeof(Date));

        fin.read((char *)&item.type.id, sizeof(int));

        ReadString(fin, item.type.name);

        fin.read((char *)&item.amount, sizeof(long long));

        ReadString(fin, item.description);

        add_element(this->expenses, this->expCount, this->expCap, item);
    }

    fin.close();
    cout << "Da load xong Wallet: " << this->name << " (ID: " << this->id << ")" << endl;
    cout << "- Income records: " << this->inCount << endl;
    cout << "- Expense records: " << this->expCount << endl;
}