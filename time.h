#ifndef TIME_H
#define TIME_H
#include <string>
#include <iostream>
using namespace std;
class Time
{
private:
    int sec;
    int hour;
    int min;

public:
    Time() : sec(0), hour(0), min(0){};
    Time(string A)
    {
        int i = 0;
        while (A[i] != 'T')
        {
            i++;
        }
        i++;
        string temp = "";
        while (A[i] != ':')
        {
            temp.push_back(A[i]);
            i++;
        }
        i++;
        hour = stoi(temp);
        temp = "";
        while (A[i] != ':')
        {
            temp.push_back(A[i]);
            i++;
        }
        i++;
        min = stoi(temp);
        temp = "";
        while (A[i] != 'Z')
        {
            temp.push_back(A[i]);
            i++;
        }
        sec = stoi(temp);
    }
    //Ostream operator overload
    friend ostream &operator<<(ostream &os, const Time &t);
};
ostream &operator<<(ostream &os, const Time &t)
{
    os << t.hour << ":" << t.min << ":" << t.sec;
    return os;
}
#endif