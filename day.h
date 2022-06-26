#ifndef DAY_H
#define DAY_H
#include <iostream>
#include <string>
using namespace std;
class Day
{
private:
    int month;
    int day;
    int year;

public:
    //Constructor

    Day() : month(0), year(0), day(0){};

    Day(string A)
    {
        string temp = "";
        int i = 0;
        while (A[i] != '-')
        {
            temp.push_back(A[i]);
            i++;
        }
        year = stoi(temp);
        i++;
        temp = "";
        while (A[i] != '-')
        {
            temp.push_back(A[i]);
            i++;
        }
        i++;
        month = stoi(temp);
        temp = "";
        while (A[i] != 'T')
        {
            temp.push_back(A[i]);
            i++;
        }
        day = stoi(temp);
    }
    //Relational Operator Overload
    bool operator<(const Day &d)
    {
        if (d.year < this->year)
            return false;
        else
        {
            if (d.month < this->month)
                false;
            else
            {
                if (d.day < this->day)
                    false;
            }
        }
        if (d.year == this->year && d.month == this->month && d.day == this->day)
            return false;
        return true;
    }
    //Ostream operator overload
    friend ostream &operator<<(ostream &os, const Day &d);
};
ostream &operator<<(ostream &os, const Day &d)
{
    os << d.year << "-" << d.month << "-" << d.day;
    return os;
}
#endif