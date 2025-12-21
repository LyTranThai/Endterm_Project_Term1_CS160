#include <string>
#pragma once

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
