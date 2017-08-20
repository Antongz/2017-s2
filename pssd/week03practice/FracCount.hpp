/*
 * =====================================================================================
 *
 *       Filename:  FracCount.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/12/2017 06:00:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <math.h>
#include <stdio.h>


using namespace std;

class FracCount{

public:
    int position(int numerator,int denominator){
        int res = 0;
        while(true){
            if(checkGCD(numerator,denominator)==1){
                res++;
                if(numerator==1&&denominator==2)
                    break;
            }
            numerator--;
            if(numerator==1){
                denominator--;
                numerator = denominator - 1;
            }
        }

        return res;
    }

    int checkGCD(int numerator,int denominator){
        int c = 0;
        while(numerator!=0){
            c = numerator;
            numerator = denominator%numerator;
            denominator = c;
        }

        return denominator;
    }

};
