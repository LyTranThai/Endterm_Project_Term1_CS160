#include "../header/Date.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

bool IsValidCalendarDate(int d, int m, int y) 
{
    if (y < 1900 || y > 3000) return false; // Reasonable limits for finance
    if (m < 1 || m > 12) return false;

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Leap year check: Divisible by 4 AND (not divisible by 100 OR divisible by 400)
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        daysInMonth[2] = 29;
    }

    return d > 0 && d <= daysInMonth[m];
}

// Input a date (from console).
Date InputDate(string info)
{
Date errorDate = {0, 0, 0}; // Return this if input is invalid
    
    if (info.empty()) return errorDate;

    // 1. Normalize Separators
    // Replace '-' or '.' with '/' to handle formats like 12-05-2024
    string cleanInfo = info;
    for (char &c : cleanInfo) {
        if (c == '-' || c == '.') c = '/';
    }

    stringstream ss(cleanInfo);
    string segment;
    vector<int> parts;

    // 2. Split string by '/'
    while (getline(ss, segment, '/')) {
        try {
            size_t pos;
            int val = stoi(segment, &pos);
            
            // Ensure the segment was fully numeric (avoids "12abc" being read as 12)
            if (pos != segment.size()) return errorDate; 
            
            parts.push_back(val);
        } catch (...) {
            return errorDate;
        }
    }

    // 3. Check if we got exactly 3 parts (Day, Month, Year)
    if (parts.size() != 3) return errorDate;

    int d = parts[0];
    int m = parts[1];
    int y = parts[2];

    // 4. Handle shorthand years (e.g., input "23" -> "2023")
    if (y < 100) {
        y += 2000;
    }

    // 5. Logical Validation
    if (!IsValidCalendarDate(d, m, y)) {
        return errorDate;
    }

    // 6. Success
    Date result;
    result.day = d;
    result.month = m;
    result.year = y;
    return result;
};

// Output a date (to console). Format: DD/MM/YYYY
void OutputDate(Date src)
{
    cout<<setw(5)<<right<<src.day<<"/"<<src.month << "/" << src.year;
}
// Input a date (from text file).
void InputDate(ifstream& fin)
{
    string file_name;
    cout<<"Nhap ten file: ";
    cin>>file_name;
    string info;
    fin.open(file_name);
    if(fin.is_open())
    {
        getline(fin,info);
        InputDate(info);
        fin.close();
    }
};

// Output a date (yyyy-MM-dd) (to text file).
void OutputDate(ofstream& fout,Date src)
{
    fout.open("output.txt",ios::app);
    if(fout.is_open())
    {
        fout<<src.day<<"/"<<src.month << "/" << src.year << endl;
        fout.close();
    }
};

// Output a date with a given format (to Date_Output.txt with app mode). For example: yy: 70, yyyy: 1970, M: 8 or 12,
void OutputDateFormat(Date src, string format)
{
    ofstream fout;
    fout.open("Date_output.txt",ios::app);
    int count=0;
    string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int day=0;
    int month=0;
    int year=0;
    for (int i=0; i<format.length(); i++)
    {
        
        if(format[i]== 'D' || format[i]== 'd')
        {
            format[i]='D';
            day+=1;
        }
        if(format[i]=='M' || format[i]=='m')
        {
            format[i]='M';
            month+=1;
        }
        if(format[i]=='Y' || format[i]=='y')
        {
            format[i]='Y';
            year+=1;
        }
        if(day>2 || month>3|| year>4)
        {
            cout << "\nError format\n";
            return;
        }
    }
    for(int i=0; i<format.length(); i++)
    {
        if(format[i]=='D')
        {
            fout<<src.day<<" ";
            while(format[i]=='D')
            {
                continue;
            }
        }
        else if (format[i] == 'M')
        {
            if(month ==3)
            {
                fout<<months[src.month-1]<<" ";
                i+=2;
            }
            else if(month <= 2)
            {
                fout<<src.month<<" ";
                while(format[i]=='M')
            {
                continue;
            }
            }
            

        }
        else if (format[i] == 'Y')
        {
            if (year == 4)
            {
                fout << src.year << " ";
                i+=3;
            }
            else if (year <= 2)
            {
                fout << src.year % 100<<" ";
            }
            else
            {
                fout<< "\nError format for year\n";
            }
        }
    }
    fout.close();
}



Date GetCurrentDate(Date& current_date)
{
    
    time_t now = time(0);
    tm *ltm = localtime(&now);

    current_date.day = ltm->tm_mday;
    current_date.month = 1 + ltm->tm_mon;
    current_date.year = 1900 + ltm->tm_year;

    return current_date;
}

//check nawm nhuan
bool nam_nhuan(int year)
{
    if((year % 4 == 0 && year % 100 == 0) || (year % 400 == 0))
    {
        return true;
    }
    return false;
}

int Days_of_year(int year)
{
    if((year % 4 == 0 && year % 100 == 0) || (year % 400 == 0))
    {
        return 366;
    }
    return 365;
}
// x<=y, so sanh hai thang  cung nam
int month_diff(int x,int y, int year)
{
    int daysInMonth[13] = {0,31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31};
    if(nam_nhuan(year))
    {
        daysInMonth[2]=29;
    }
    int sum=0;
    for(int i=x; i< y; i++)
    {
        sum+=daysInMonth[i];
    }
    return sum;
}
//year1<year2, so sanh 2 nam
int year_diff(int year1, int year2)
{
    int sum = 0;
    for(int i = year1; i < year2; i++)
    {
        if(nam_nhuan(i))
        {
            sum += 366;
        }
        else
        {
            sum+=365;
        }
    }
    return sum;
}



// Compare 2 date.


int compare(Date Date1,Date Date2)
{
    int min = Date1.year>Date2.year?Date2.year:Date1.year;
    min -= 1;
    int pos1 = Date1.day-1 + month_diff(1,Date1.month,Date1.year) + year_diff(min,Date1.year);
    int pos2 = Date2.day-1 + month_diff(1,Date2.month,Date2.year) + year_diff(min,Date2.year);
    if(pos1==pos2) return 0;
    Date save;
    if (pos1>pos2)
    {
        save=Date1;
        Date1=Date2;
        Date2=save;
    }
    int sum =0;
    sum+=year_diff(Date1.year,Date2.year);
    sum+= Date1.day-1 + month_diff(1,Date1.month,Date1.year);
    sum-= Date2.day-1 + month_diff(1,Date2.month,Date2.year);
    return sum;
}
// Find tomorrow: increase a date by 1 day.
void tommorow(Date& src)
{
    int daysInMonth[13] = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    src.day += 1;
    if(src.day>daysInMonth[src.month])
    {
        src.day=1;
        src.month+=1;
    }
    if(src.month>12)
    {
        src.month=1;
        src.year += 1;
    }
}

//Find yesterday: decrease a date by 1 day.
void yesterday(Date& src)
{
    int daysInMonth[13] = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    src.day -= 1;
    if(src.day==0)
    {
        src.month-=1;
    }
    if(src.month==0)
    {
        src.year -= 1;
        src.month=12;
    }
    src.day=daysInMonth[src.month];
}

//Increase a date by k day.
void IncreasekDate(Date& src, int k)
{
    int daysInMonth[13] = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day= src.day;
    src.day += k;
    if(src.day>daysInMonth[src.month])
    {
        src.day-=(1 + daysInMonth[src.month]-day);
        src.month+=1;
        if(src.month>12)
            {
                src.month=1;
                src.year += 1;
            }
    }
    while(src.day>daysInMonth[src.month])
    {
    {
        src.day-=(daysInMonth[src.month]) ;
        src.month+=1;
    }
    if(src.month>12)
    {
        src.month=1;
        src.year += 1;
    }
    }
}

//Decrease a date by k day.
void DecreasekDate(Date& src, int k)
{
    int daysInMonth[13] = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day=src.day;
    src.day -= k;
    if(src.day <= 0)
    {
        src.day += (day-1);
    }
    while(src.day<=0)
    {
    {
        src.day+=(daysInMonth[src.month]);
        src.month-=1;
    }
    if(src.month<=0)
    {
        src.month=12;
        src.year -= 1;
    }
    if(src.year <= 0)
    {
        cout<<"It's on BC"<<endl;
        return;
    }
    }
}

// Compute the distance between input date vs 1/1/same year.
int year_begin(Date src)
{
    return month_diff(1,src.month,src.year)+ src.day-1;
}

// Compute the distance between input date vs 1/1/1970.
int SinceDate(Date src)
{
    Date Date1;
    Date1.day=1;
    Date1.month=1;
    Date1.year=1970;
    return compare(Date1,src);
}

// Given that the date of week of 1970-01-01 is Thursday. Compute the date of week of the input
string which_day_of_week(Date src)
{
    int distance=SinceDate(src);
    int week= distance %7;
    string daysOfWeek[7] = {"Thursday",
    "Friday", "Saturday", "Sunday","Monday", "Tuesday", "Wednesday"};
    return daysOfWeek[week];
}


int compare_Date(Date day1, Date day2)
{
    Date current;
    current.day=1;
    current.month=1;
    current.year=1800;
    int age1=compare(day1,current);
    int age2=compare(day2,current);
    if(age1>age2)
    {
        return 1;
    }
    else if(age1<age2)
    {
        return 2;
    }
    else
    {
        return 3;
    }

}

Date Get_Last_Date_Month(Date date)
{
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int y=date.year;
    // Leap year check: Divisible by 4 AND (not divisible by 100 OR divisible by 400)
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        daysInMonth[2] = 29;
    }
    date.day=daysInMonth[date.month];
    return date;
}