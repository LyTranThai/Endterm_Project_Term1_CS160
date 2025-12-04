#include <string>

struct MasterData
{
    int id;
    std::string name;
};

struct ExpenseCategory : MasterData
{
};

struct IncomeSource : MasterData
{
};

struct Wallet : MasterData
{
    double balance;
};
