/*
 * =====================================================================================
 *
 *       Filename:  RoughStrings.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/10/2017 03:05:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define found(s,e)  ((s).find(e)!=(s).end())
#define remove_(c,val) (c).erase(remove((c).begin(),(c).end(),(val)),(c).end())

class RoughStrings{
    map<vector<int>,int> memo;
    int n_ = 0;

    int find(vector<int> count,int d){
        remove_(count,0);
        if(found(memo,count))
            return memo[count];
        int length = count.size();
        if(length<=1)
            return 0;
        sort(count.begin(),count.end());
        int res = 0;
        res = count[length-1] - count[0];
        if(d==n_)
            return memo[count] = res;
        if(count[0]>0){
            count[0]--;
            res = min(res,find(count,d+1));
            count[0]++;
        }
        count[length-1]--;
        res = min(res,find(count,d+1));
        count[length-1]++;
        return memo[count] = res;
    }


public:
    int minRoughness(string s,int n){
        string temp = "";
        map<vector<int>,int> new1;
        memo = new1;
        vector<string> charS;
        vector<int> count;
        for(int i=0;i<(int)s.length();i++){
            temp = s[i];
            bool check = true;
            for(int j=0;j<(int)charS.size();j++){
                if(temp==charS[j]){
                    count[j]++;
                    check = false;
                    break;
                }
            }
            if(check){
                charS.push_back(temp);
                count.push_back(1);
            }
        }
        sort(count.begin(),count.end());
        n_ = n;
        return find(count,0);
    }

};
