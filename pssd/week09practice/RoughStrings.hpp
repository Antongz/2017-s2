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

using namespace std;

class RoughStrings{

public:
    int minRoughness(string s,int n){
        string temp = "";
        vector<string> charS;
        vector<int> count;
        for(int i=0;i<(int)s.size();i++){
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
        int posm = 0;
        int posM = count.size()-1;
        int res = count[posM] - count[posm];
        for(int i=1;i<=n;i++){
            posm = 0;
            posM = count.size()-1;
            sort(count.begin(),count.end());

            if(count[posm]==1){
                if(res>count[posM]-count[posm+1]){
                    posm++;
                    res = count[posM] - count[posm];
                    if(res==0)
                        break;
                }
            }
            if(res>abs(count[posM]-1-count[posm])){
                res = abs(count[posM]-1-count[0]);
                count[posM]--;
                if(res==0)
                    break;
            }
        }

        return res;
    }

};
