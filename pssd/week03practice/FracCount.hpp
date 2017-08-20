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
            if(numerator==1&&denominator==2)
                return 1;
            if(numerator==1)
                return 1+position(denominator-2,denominator-1);
            else{
				if(denominator-numerator==1)
					return 1+position(numerator-1,denominator);
                if(checkGCD(numerator,denominator))
                    return position(numerator-1,denominator);
                else
                    return 1+position(numerator-1,denominator);
            }

		}
        bool checkGCD(int numerator,int denominator){
            int tmp = numerator;
            int c = denominator % numerator;
            if(c==0){
                return true;
            }
            if(denominator<numerator){
                return false;
            }
            else{
                return checkGCD(numerator,c);
            }
			
		}

};
