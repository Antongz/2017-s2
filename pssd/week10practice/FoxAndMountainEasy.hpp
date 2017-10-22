/*
 * =====================================================================================
 *
 *       Filename:  FoxAndMountainEasy.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/20/17 01:05:23
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
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class FoxAndMountainEasy{

public:
    string possible(int n,int h0,int hn,string history){
        vector<int> check;
        for(int i=0;i<(int)history.length();i++){
            if(history[i]=='U')
                check.push_back(1);
            else if(history[i]=='D')
                check.push_back(-1);
        }
        int array[n];
        const int anInt = sizeof(anInt);
        fill(array,array+sizeof(array)/anInt,0);
        array[0] = h0;
        int itr = 0;
        bool check1 = true;
        bool c = true;
        while(n-(itr+1)>=0){
            //cout << itr << " ";
            int counter = h0;
            for(int i=0;i<=itr;i++){
                counter += array[i];
            }
            if(check1){
                if(itr+1+(int)check.size()>n)
                    return "NO";
                c = true;
                for(int i=0;i<(int)check.size();i++){
                    counter += check[i];
                    if(counter<0){
                        c = false;
                        break;
                    }
                }
                if(c){
                    for(int i=0;i<(int)check.size();i++){
                        array[itr+i] = check[i];
                    }
                    itr += (int)check.size()-1;
                    check1 = false;
                }else{
                    array[itr] = 1;
                }
            }else{
                if(counter<=hn)
                    array[itr] = 1;
                else
                    array[itr] = -1;
            }
            itr++;
        }
        //cout << endl;
        int res = h0;
        for(int i=0;i<n;i++){
            res += array[i];
            //cout << array[i] << " ";
        }
        //cout << endl;
        //cout << res << endl;
        if(res==hn)
            return "YES";
        return "NO";
    }

};
