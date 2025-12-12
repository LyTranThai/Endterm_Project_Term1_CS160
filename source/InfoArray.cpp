#include "Date.h"
#include <sstream>
#include <iomanip>
// Kiểm tra năm nhuận
bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// helper
int getDaysInMonth(int month, int year)
{
    switch (month)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return 31;
    }
}

// nhập sai ngày là bt đấy :)), I'm watching you
bool isValidDate(const Date &d)
{
    if (d.year < 1900 || d.year > 2100)
        return false;
    if (d.month < 1 || d.month > 12)
        return false;
    if (d.day < 1 || d.day > getDaysInMonth(d.month, d.year))
        return false;
    return true;
}

// chuyển date string
string dateToString(const Date &d)
{
    stringstream ss;
    ss << d.year << "-"
       << setfill('0') << setw(2) << d.month << "-"
       << setfill('0') << setw(2) << d.day;
    return ss.str();
}

// chuyển string date
bool stringToDate(const string &str, Date &outDate)
{
    if (str.length() != 10)
        return false;
    if (str[4] != '-' || str[7] != '-')
        return false;

    try
    {
        string sYear = str.substr(0, 4);
        string sMonth = str.substr(5, 2);
        string sDay = str.substr(8, 2);

        // check full số
        for (char c : sYear)
            if (!isdigit(c))
                return false;
        for (char c : sMonth)
            if (!isdigit(c))
                return false;
        for (char c : sDay)
            if (!isdigit(c))
                return false;

        outDate.year = stoi(sYear);
        outDate.month = stoi(sMonth);
        outDate.day = stoi(sDay);

        return isValidDate(outDate);
    }
    catch (...)
    {
        return false;
    }
}

bool isValidDouble(const string &s)
{
    if (s.empty())
        return false;
    bool hasDecimal = false;
    for (char c : s)
    {
        if (!isdigit(c))
        {
            if (c == '.' && !hasDecimal)
                hasDecimal = true;
            else
                return false;
        }
    }
    return true;
}

// check int
bool isValidInt(const string &s)
{
    if (s.empty())
        return false;

    size_t start = 0;
    if (s[0] == '-')
        start = 1;

    for (size_t i = start; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}
