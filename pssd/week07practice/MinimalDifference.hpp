/*
 * =====================================================================================
 *
 *       Filename:  MinimalDifference.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/2017 11:28:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>

using namespace std;

class MinimalDifference{
public:
    int findNumber(int A,int B,int C){
        int res = A;
        int help = abs(sumDigit(A)-sumDigit(C));
        int sumT = 0;
        int sumC = sumDigit(C);
        int temp = A;
        while(temp<=B){
            sumT = sumDigit(temp);
            if(abs(sumT-sumC)<help){
                res = temp;
                help = abs(sumT-sumC);
            }
            if(sumT-sumC==0)
                break;

            temp += 1;
        }

        return res;
    }

    int sumDigit(int num){
        int sum = 0;
        while(num>0){
            sum += num % 10;
            num = num / 10;
        }

        return sum;
    }
};
