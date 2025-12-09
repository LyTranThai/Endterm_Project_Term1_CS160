#include "MasterDataFunc.h"
#include <iostream>

// tìm max để thêm ID mới kh lăp

int findNextId(const MasterData *data, int size)
{
    int maxId = 0;
    for (int i = 0; i < size; ++i)
    {
        if (data[i].id > maxId)
        {
            maxId = data[i].id;
        }
    }
    return maxId + 1;
}

// Overload for Wallet which uses field name `ID` instead of `id`
// Wallet now inherits MasterData and uses `id`, so no separate overload is required.

// Tạo array cho exp
void initExpenseCategoryArray(ExpenseCategoryArray &arr)
{
    arr.size = 0;
    arr.capacity = INITIAL_CAPACITY;
    arr.data = new ExpenseCategory[arr.capacity];
}

// free
void freeExpenseCategoryArray(ExpenseCategoryArray &arr)
{
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

// x2 size cho array
void resizeExpenseCategoryArray(ExpenseCategoryArray &arr)
{

    int newCapacity = arr.capacity * 2;
    ExpenseCategory *newData = new ExpenseCategory[newCapacity];
    for (int i = 0; i < arr.size; ++i)
    {
        newData[i] = arr.data[i];
    }
    delete[] arr.data;
    arr.data = newData;
    arr.capacity = newCapacity;
}
// Tìm id
int findExpCatIndexById(const ExpenseCategoryArray &arr, int id)
{
    for (int i = 0; i < arr.size; ++i)
    {
        if (arr.data[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void addExpenseCategory(ExpenseCategoryArray &arr, const std::string &name)
{
    if (arr.size == arr.capacity)
    {
        resizeExpenseCategoryArray(arr);
    }
    // up size khi full

    ExpenseCategory newItem;
    newItem.id = findNextId(arr.data, arr.size); // tao id moi
    newItem.name = name;                         // ten

    arr.data[arr.size] = newItem;
    arr.size++;
    std::cout << "Added: " << name << " Successfully." << std::endl;
}

// call func va doi ten, con lai chua nghi ra
bool editExpenseCategory(ExpenseCategoryArray &arr, int id, const std::string &newName)
{
    int index = findExpCatIndexById(arr, id);
    if (index != -1)
    {
        arr.data[index].name = newName;
        return true;
    }
    return false;
}

bool deleteExpenseCategory(ExpenseCategoryArray &arr, int id)
{

    int index = findExpCatIndexById(arr, id);

    if (index == -1)
    {

        std::cout << "Cannot find ID = " << id << " to delete." << std::endl;
        return false;
    }

    for (int i = index; i < arr.size - 1; ++i)
    {

        arr.data[i] = arr.data[i + 1];
    }

    arr.size--;

    std::cout << "Deleted ID = " << id << " successfully." << std::endl;

    return true;
}

void initIncomeSourceArray(IncomeSourceArray &arr)
{
    arr.size = 0;
    arr.capacity = INITIAL_CAPACITY;
    arr.data = new IncomeSource[arr.capacity];
}

void freeIncomeSourceArray(IncomeSourceArray &arr)
{
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

void resizeIncomeSourceArray(IncomeSourceArray &arr)
{
    int newCapacity = arr.capacity * 2;
    IncomeSource *newData = new IncomeSource[newCapacity];

    for (int i = 0; i < arr.size; ++i)
    {
        newData[i] = arr.data[i];
    }

    delete[] arr.data;
    arr.data = newData;
    arr.capacity = newCapacity;
}

int findIncomeSrcIndexById(const IncomeSourceArray &arr, int id)
{
    for (int i = 0; i < arr.size; ++i)
    {
        if (arr.data[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void addIncomeSource(IncomeSourceArray &arr, const std::string &name)
{
    if (arr.size == arr.capacity)
    {
        resizeIncomeSourceArray(arr);
    }

    IncomeSource newItem;

    newItem.id = findNextId(arr.data, arr.size);
    newItem.name = name;

    arr.data[arr.size] = newItem;
    arr.size++;
    std::cout << "Them Nguon Thu nhap: " << name << " thanh cong." << std::endl;
}

bool editIncomeSource(IncomeSourceArray &arr, int id, const std::string &newName)
{
    int index = findIncomeSrcIndexById(arr, id);
    if (index != -1)
    {
        arr.data[index].name = newName;
        return true;
    }
    return false;
}

bool deleteIncomeSource(IncomeSourceArray &arr, int id)
{
    int index = findIncomeSrcIndexById(arr, id);

    if (index == -1)
    {
        std::cout << "Cannot find ID = " << id << " to delete." << std::endl;
        return false;
    }

    for (int i = index; i < arr.size - 1; ++i)
    {
        arr.data[i] = arr.data[i + 1];
    }

    arr.size--;

    std::cout << "Deleted ID = " << id << " successfully." << std::endl;

    return true;
}

void initWalletArray(WalletArray &arr)
{
    arr.size = 0;
    arr.capacity = INITIAL_CAPACITY;
    arr.data = new Wallet[arr.capacity];
}

void freeWalletArray(WalletArray &arr)
{
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

void resizeWalletArray(WalletArray &arr)
{
    int newCapacity = arr.capacity * 2;
    Wallet *newData = new Wallet[newCapacity];

    for (int i = 0; i < arr.size; ++i)
    {
        newData[i] = arr.data[i];
    }

    delete[] arr.data;
    arr.data = newData;
    arr.capacity = newCapacity;
}

int findWalletIndexById(const WalletArray &arr, int id)
{
    for (int i = 0; i < arr.size; ++i)
    {
        if (arr.data[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void addWallet(WalletArray &arr, const std::string &name)
{
    if (arr.size == arr.capacity)
    {
        resizeWalletArray(arr);
    }

    Wallet newItem;
    newItem.id = findNextId(arr.data, arr.size);
    newItem.name = name;
    newItem.remain = 0.0;

    arr.data[arr.size] = newItem;
    arr.size++;
    std::cout << "Them Vi tien: " << name << " thanh cong. So du ban dau: 0.0" << std::endl;
}

bool editWallet(WalletArray &arr, int id, const std::string &newName)
{
    int index = findWalletIndexById(arr, id);
    if (index != -1)
    {
        arr.data[index].name = newName;
        return true;
    }
    return false;
}

bool deleteWallet(WalletArray &arr, int id)
{
    int index = findWalletIndexById(arr, id);

    if (index == -1)
    {
        std::cout << "Cannot find ID = " << id << " to delete." << std::endl;
        return false;
    }

    for (int i = index; i < arr.size - 1; ++i)
    {
        arr.data[i] = arr.data[i + 1];
    }

    arr.size--;

    std::cout << "Deleted ID = " << id << " successfully." << std::endl;

    return true;
}