#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "day.h"
#include "time.h"
#include "transaction.h"
#include "toData.h"
using namespace std;
int main()
{
  
  string fileName;
  cout<<"Enter the Input Filename : ";
  cin>>fileName;
  freopen("output.txt", "w", stdout);
  //open csv file
  fstream fin(fileName);
  if (!fin.is_open())
    cout << "Error in opening file" << endl; ///
  string line, word, check;
  vector<string> rowData;
  Day currentDay;
  Day firstDay;
  vector<Transaction> ans;
  ans.clear();
  double dayMin;
  double dayMax;
  //reading firstDay data
  if (fin.good())
  {
    rowData.clear();
    getline(fin, line); //column headings are removed as temp line
    getline(fin, line);
    rowData = toData(line);
    firstDay = Day(rowData[0]);
    dayMin = min(stod(rowData[2]), stod(rowData[3]));
    dayMax = max(stod(rowData[2]), stod(rowData[3]));
  }
  else
  {
    cout << "ERROR In reading " << endl;
  }
  while (getline(fin, line))
  {
    rowData.clear();
    rowData = toData(line);
    currentDay = Day(rowData[0]);
    if (firstDay < currentDay)
    {
      firstDay = currentDay;
      break;
    }
    double cOpen = min(stod(rowData[2]), stod(rowData[3]));
    double cClose = max(stod(rowData[2]), stod(rowData[3]));
    dayMin = min(cOpen, dayMin);
    dayMax = max(dayMax, cClose);
  }
  //end of day1 data

  //day2 starts
  double sellP = 2.0 * dayMax - dayMin;
  double buyP = dayMax;
  double stopLoss = dayMax - (dayMax - dayMin) * 0.25;
  bool status = false;
  dayMin = min(stod(rowData[2]), stod(rowData[3]));
  dayMax = max(stod(rowData[2]), stod(rowData[3]));
  while (!fin.eof())
  {
    if (!status)
    {
      if (stod(rowData[3]) <= buyP && buyP <= stod(rowData[2]))
      {
        status = true;
        Transaction temp = Transaction();
        temp.buyPrice = buyP;
        temp.buyDay = Day(rowData[0]);
        temp.buyTime = Time(rowData[0]);
        ans.push_back(temp);
      }
    }
    while (getline(fin, line))
    {
      double lastPrice = stod(rowData[2]);
      Time lastTime = Time(rowData[0]);
      rowData.clear();
      rowData = toData(line);
      currentDay = Day(rowData[0]);
      if (firstDay < currentDay)
      {
        if (status)
        {
          ans[ans.size() - 1].sellDay = firstDay;
          ans[ans.size() - 1].sellPrice = lastPrice;
          ans[ans.size() - 1].sellTime = lastTime;
          ans[ans.size() - 1].profit = 10 * (ans[ans.size() - 1].sellPrice - ans[ans.size() - 1].buyPrice);
          ans[ans.size() - 1].status = false;
          status = false;
        }
        firstDay = currentDay;
        break;
      }
      double cOpen = stod(rowData[3]);
      double cClose = stod(rowData[2]);
      dayMin = min(cOpen, dayMin);
      dayMax = max(dayMax, cClose);
      if (!status)
      {
        if ((stod(rowData[3]) <= buyP && buyP <= stod(rowData[2])))
        {
          status = true;
          Transaction temp = Transaction();
          temp.buyPrice = buyP;
          temp.buyDay = Day(rowData[0]);
          temp.buyTime = Time(rowData[0]);
          ans.push_back(temp);
        }
      }
      else
      {
        if ((stod(rowData[3]) <= stopLoss && stod(rowData[2]) >= stopLoss) || (stod(rowData[2]) >= sellP && stod(rowData[3]) <= sellP))
        {
          if (stod(rowData[3]) <= stopLoss && stod(rowData[2]) >= stopLoss)
          {
            ans[ans.size() - 1].sellPrice = stopLoss;
            ans[ans.size() - 1].profit = 10 * (stopLoss - ans[ans.size() - 1].buyPrice);
            ans[ans.size() - 1].sellDay = Day(rowData[0]);
            ans[ans.size() - 1].sellTime = Time(rowData[0]);
            ans[ans.size() - 1].status = false;
            status = false;
          }
          else
          {
            ans[ans.size() - 1].sellPrice = sellP;
            ans[ans.size() - 1].profit = 10 * (sellP - ans[ans.size() - 1].buyPrice);
            ans[ans.size() - 1].sellDay = Day(rowData[0]);
            ans[ans.size() - 1].sellTime = Time(rowData[0]);
            ans[ans.size() - 1].status = false;
            status = false;
          }
        }
      }
    }
    
    sellP = 2.0 * dayMax - dayMin;
    buyP = dayMax;
    stopLoss = dayMax - (dayMax - dayMin) * 0.25;
    

    dayMin = stod(rowData[3]);
    dayMax = stod(rowData[2]);
  }
  for (int i = 0; i < ans.size(); i++)
  {
    cout << ans[i] << endl;
  }
  return 0;
}