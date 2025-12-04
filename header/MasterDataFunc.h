#ifndef MASTER_DATA_FUNCS_H
#define MASTER_DATA_FUNCS_H

#include "DynamicArray.h"
#include <string>

void initExpenseCategoryArray(ExpenseCategoryArray &arr);
void freeExpenseCategoryArray(ExpenseCategoryArray &arr);
void resizeExpenseCategoryArray(ExpenseCategoryArray &arr);

int findExpCatIndexById(const ExpenseCategoryArray &arr, int id);
void addExpenseCategory(ExpenseCategoryArray &arr, const std::string &name);
bool editExpenseCategory(ExpenseCategoryArray &arr, int id, const std::string &newName);
bool deleteExpenseCategory(ExpenseCategoryArray &arr, int id);

void initIncomeSourceArray(IncomeSourceArray &arr);
void freeIncomeSourceArray(IncomeSourceArray &arr);
void resizeIncomeSourceArray(IncomeSourceArray &arr);

int findIncomeSrcIndexById(const IncomeSourceArray &arr, int id);
void addIncomeSource(IncomeSourceArray &arr, const std::string &name);
bool editIncomeSource(IncomeSourceArray &arr, int id, const std::string &newName);
bool deleteIncomeSource(IncomeSourceArray &arr, int id);

void initWalletArray(WalletArray &arr);
void freeWalletArray(WalletArray &arr);
void resizeWalletArray(WalletArray &arr);

int findWalletIndexById(const WalletArray &arr, int id);
void addWallet(WalletArray &arr, const std::string &name);
bool editWallet(WalletArray &arr, int id, const std::string &newName);
bool deleteWallet(WalletArray &arr, int id);

#endif