#include "../header/DataHandling.h"


void WriteString(ofstream &out, const string &s)
{
    size_t len = s.size();
    out.write((char *)&len, sizeof(len)); // xâu length
    if (len > 0)
    {
        out.write(s.c_str(), len); // print xau
    }
}

// đọc xâu
void ReadString(ifstream &in, string &s)
{
    size_t len = 0;
    in.read((char *)&len, sizeof(len));
    if (in.gcount() != sizeof(len))
        return;

    if (len > 0)
    {
        s.resize(len);
        in.read(&s[0], len);
    }
    else
    {
        s = "";
    }
}


    template <typename T>
    void resize1(T** & p, int size, int cap)
    {
        while(size>=cap)
        {
            cap *= 2;
            
        }
        T**dummy=p;
        p= new T*[cap];
        for(int i=0; i<size; i++)
        {
            p[i]=dummy[i];
        }
        delete[]dummy;
    }

    template <typename T>
    bool Find_By_ID(int& id,T**& list, int& size,T*& pointer)
    {
        check=false;
        for(int i=0; i<size; i++)
        {
            if(list[i]->id==id)
            {
                pointer=list[i];
                check=true;
                break;
            }
        }
        if(!check)
        {
            pointer=list[0];
        }
        return check;
    }

template <typename T>
bool Find_By_Name(string& name,T**& list, int& size,T*& pointer)
{
    check=false;
        for(int i=0; i<size; i++)
        {
            if(compare_string(name, list[i]->name))
            {
                pointer=list[i];
                check=true;
                break;
            }
        }
        if(!check)
        {
            pointer=list[0];
        }
    return check;
}

bool compare_string(string& s1, string& s2)
{
    if(s1.size() != s2.size())
    {
        return false;
    }
    for(int i =0; i<s1.size(); i++)
    {
        if(s1[i]!=s2[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
int Generate_ID(T** list, int count) 
{
    if (count == 0) return 1; // Start at 1 if list is empty

    int max_id = 0;
    for (int i = 0; i < count; i++) {
        if (list[i]->id > max_id) {
            max_id = list[i]->id;
        }
    }
    return max_id + 1;
}

bool check_string(string info, char c)
{
    for(int i=0; i<info.size(); i++)
    {
        if(info[i]==c)
        {
            return true;
        }
    }
    return false;
}


void Clear_Buffer()
{
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void ClearLines(int numLines) 
{
    for (int i = 0; i < numLines; i++) 
    {
        // \033[A moves cursor up 1 line
        // \033[2K clears the entire line
        cout << "\033[A" << "\033[2K";
    }
}