/*
 * =====================================================================================
 *
 *       Filename:  RugSizes.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/24/2017 11:27:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

class RugSizes{

	public:
        int rugCount(int area){
            int res = 0;
            int itr = 1;

            while(itr<=area/2){
                if(area%itr==0){
                    if(itr%2==0&&(area/itr)%2==0&&itr!=(area/itr))
                        ;
                    else
                        res++;
                }
                itr++;
            }

            return res;
        }

};
