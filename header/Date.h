/*
// 25125048
// Lý Trần Thái
// 25A01
//This is source code for struct Date
*/
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
struct Date
{
    int day;
    int month;
    int year;
    Date& operator= (const Date& other)
    {
        if (this == &other) 
        {
        return *this;
        }

        this->day=other.day;
        this->month=other.month;
        this->year=other.year;
        return *this;
    }
    bool operator==(const Date& other) const
    {
        return (this->day == other.day && 
                this->month == other.month && 
                this->year == other.year);
    }

};


// Input a date (from console).
Date InputDate(string info);

// Output a date (to console).
void OutputDate(Date src);

// Input a date (from text file).
void InputDate(ifstream& fin);

// Output a date (yyyy-MM-dd) (to text file).
void OutputDate(ofstream& fout,Date src);

// Output a date with a given format (to text file). For example: yy: 70, yyyy: 1970, M: 8 or 12,
void OutputDateFormat(Date src, string format);

// Get current Date
Date GetCurrentDate(Date& current_date);

// Compare 2 date, return their distance until other date
int compare(Date Date1,Date Date2);

// Find tomorrow: increase a date by 1 day.
void tommorow(Date& src);

// outputDateWithFormat(d1, "MMM dd yy"); // Dec 12 19
void yesterday(Date& src);

//Increase a date by k day.
void IncreasekDate(Date& src, int k);

// Find yesterday: decrease a date by 1 day.
void DecreasekDate(Date& src, int k);

// Compute the distance between input date vs 1/1/same year.
int year_begin(Date src);

// Compute the distance between input date vs 1/1/1970.
int SinceDate(Date src);

// Given that the date of week of 1970-01-01 is Thursday. Compute the date of week of the input
string which_day_of_week(Date src);


int compare_Date(Date day1, Date day2);
