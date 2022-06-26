#ifndef TODATA_H
#define TODATA_H
#include<string>
#include<vector>
using namespace std;
vector<string> toData(string A)
{
  vector<string> ans;
  string temp = "";
  for (int i = 0; i < A.size(); i++)
  {
    if (A[i] == ',' || A[i] == '\n')
    {
      ans.push_back(temp);
      temp = "";
    }
    else
    {
      temp.push_back(A[i]);
    }
  }
  return ans;
}
#endif