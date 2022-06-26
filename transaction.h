#ifndef TRANSACTION_H
#define TRANSACTION_H
#include<iostream>
#include<iomanip>
#include"day.h"
#include"time.h"
using namespace std;
//Transaction Class StartsS
class Transaction{
    public:
    float buyPrice;
    float sellPrice;
    Day buyDay;
    Day sellDay;
    Time buyTime;
    Time sellTime;
    bool status;
    float profit;
    //Constructor
    Transaction():sellPrice(-1),status(true){};
    //Ostream operator overload
    friend ostream& operator<<(ostream& os, const Transaction& t);
};
ostream& operator<<(ostream& os, const Transaction& t){
        if(t.status){
            os<<"Status    : InComplete"<<endl;
            os<<fixed<<setprecision(2)<<"BuyPrice  : "<<t.buyPrice<<endl;
            os<<"BuyDate   : "<<t.buyDay<<endl<<"BuyTime   : "<<t.buyTime<<endl;
            
        }
        else{
            os<<"Status    : Complete"<<endl;
            os<<fixed<<setprecision(2)<<"BuyPrice  : "<<t.buyPrice<<endl;
            os<<"BuyDate   : "<<t.buyDay<<endl<<"BuyTime   : "<<t.buyTime<<endl;
            os<<fixed<<setprecision(2)<<"SellPrice : "<<t.sellPrice<<endl;
            os<<"SellDate  : "<<t.sellDay<<endl<<"SellTime  : "<<t.sellTime<<endl;
            os<<fixed<<setprecision(2)<<"Profit    : "<<t.profit<<endl;
        }
        return os;
    }
//Transaction Class ends
#endif