/*
 * =====================================================================================
 *
 *       Filename:  GoodHours.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/10/2017 12:28:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <map>

using namespace std;

class GoodHours{


public:
    int howMany(string beforeTime,string afterTime){
        int beT[4] = {0,0,0,0};
        int afT[4] = {0,0,0,0};
        char *temp = new char [beforeTime.length()+1];
        strcpy(temp,beforeTime.c_str());
        int tem1 = stoi(strtok(temp,":"));
        int tem2 = stoi(strtok(NULL,""));
        beT[0] = tem1/10;   beT[1] = tem1%10;
        beT[2] = tem2/10;   beT[3] = tem2%10;

        temp = new char [afterTime.length()+1];
        strcpy(temp,afterTime.c_str());
        tem1 = stoi(strtok(temp,":"));
        tem2 = stoi(strtok(NULL,""));
        afT[0] = tem1/10;   afT[1] = tem1%10;
        afT[2] = tem2/10;   afT[3] = tem2%10;

        int res = 0;
        int curT[4];
        for(int i=0;i<4;i++)
            curT[i] = beT[i];

        bool check = true;
        while(check){
            if(curT[0]==curT[1]*curT[2]*curT[3])
                res++;
            else if(curT[0]*curT[1]==curT[2]*curT[3])
                res++;
            else if(curT[0]*curT[1]*curT[2]==curT[3])
                res++;

            if(curT[0]==afT[0]&&curT[1]==afT[1]&&curT[2]==afT[2]&&curT[3]==afT[3])
                check = false;

            curT[3]++;
            if(curT[3]==10)
                curT[2] += 1, curT[3] = 0;
            if(curT[2]==6)
                curT[1] += 1, curT[2] = 0;
            if(curT[1]==10)
                curT[0] += 1, curT[1] = 0;
            if(curT[0]==2&&curT[1]==4)
                curT[1] = 0,  curT[0] = 0;

        }

        return res;
    }
};
