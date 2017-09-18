/*
 * =====================================================================================
 *
 *       Filename:  LostParentheses.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/2017 11:50:43 PM
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
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <map>

using namespace std;
typedef pair<int,int> ii;

class LostParentheses{

public:
    int minResult(string e){
        vector<int> num;
        int itr = 0;
        int tempN = 0;
        int tempV = 0;
        int tempPlus = 0;
        bool checkMinus = false;
        bool checkOp = false;
        while(itr<(int)e.length()){
            if(isdigit(e[itr])){
                int temp = 0;
                switch(e[itr]){
                    case '0':
                        temp = 0;
                        break;
                    case '1':
                        temp = 1;	break;
                    case '2':
                        temp = 2;	break;
                    case '3':
                        temp = 3;	break;
                    case '4':
                        temp = 4;	break;
                    case '5':
                        temp = 5;	break;
                    case '6':
                        temp = 6;	break;
                    case '7':
                        temp = 7;	break;
                    case '8':
                        temp = 8;	break;
                    case '9':
                        temp = 9;	break;
                }
                tempN = tempN*10 + temp;
            }else{
                switch(e[itr]){
                    case '+':
                        if(checkMinus)
                            num.push_back(tempN*(-1));
                        else
                            num.push_back(tempN);
                        break;
                    case '-':
                        if(checkMinus){
                            checkMinus = false;
                            num.push_back(tempN);
                        }else{
                            checkMinus = true;
                            num.push_back(tempN);
                        }
                        break;
                }
                tempN = 0;
            }
            itr++;
        }
        if(checkMinus)
            num.push_back(tempN*(-1));
        else
            num.push_back(tempN);
        int res = 0;
        for(int i=0;i<(short)num.size();i++)
            res += num[i];

        return res;
    }
};
