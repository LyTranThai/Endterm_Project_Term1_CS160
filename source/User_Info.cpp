#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\User_Info.h"

void User_Info::sort_Transaction_List_Date()
{
    // Loop through the history using 'trans_count'
    for(int i = 0; i < this->trans_count; i++)
    {
        for(int j = i + 1; j < this->trans_count; j++)
        {
            // Access 'Transaction_History' instead of 'Transaction_List'
            if(compare_Date(this->Transaction_History[i].date, this->Transaction_History[j].date) == 2)
            {
                // Swap the transactions in the History array
                Transaction save = Transaction_History[i];
                Transaction_History[i] = Transaction_History[j];
                Transaction_History[j] = save;
            }
        }   
    }
}