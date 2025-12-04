#include "C:\Users\Admin\Documents\GitHub\Endterm_Project_Term1_CS160\header\User_Info.h"

void User_Info::sort_Transaction_List_Date()
{
    for(int i=0;i<this->number_of_transaction; i++)
    {
        for(int j=i+1; j<this->number_of_transaction; j++)
        {
        if(compare_Date(this->Transaction_List[i].date,this->Transaction_List[j].date)==2)
        {
            Transaction save = Transaction_List[i];
            Transaction_List[i]=Transaction_List[j];
            Transaction_List[j]=save;
        }
        }   
    }
}