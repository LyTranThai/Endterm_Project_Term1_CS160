#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    cout<<string(20,'-')<<"AA\n";
    //Print Hello World! aligned center to the line above
    cout<<setw(15)<<"Hello World!"<<endl;
    
    return 0;
}