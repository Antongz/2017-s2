/*
 * =====================================================================================
 *
 *       Filename:  TimeTravellingCellar.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/26/2017 12:53:50 AM
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
#include <algorithm>
using namespace std;

class TimeTravellingCellar{


	public:
        int determineProfit(vector<int> profit,vector<int> decay){
            int itr1 = 0;
            int itr2 = 0;
            int itrm1 = 0;
            int itrm2 = 0;
            int min = decay[0];
            int min2 = 1000000;
            int max2 = 0;
            int max = profit[0];
            int size = profit.size();
            //find max 2 values
            for(int i=0;i<size;i++){
                if(profit[i]>max){
                    itr2 = itr1;
                    max = profit[i];
                    itr1 = i;
                }else{
                    if(profit[i]>max2){
                        itr2 = i;
                        max2 = profit[i];
                    }

                }
            }
            //find min 2 values
            for(int i=0;i<size;i++){
                if(decay[i]<=min){
                    itrm2 = itrm1;
                    min = decay[i];
                    itrm1 = i;
                }else{
                    if(profit[i]<min2){
                        itrm2 = i;
                        min2 = profit[i];
                    }
                }

            }
            int res1 = profit[itr1]-decay[itrm2];
            int res2 = profit[itr2]-decay[itrm1];
            //int res = max(res1,res2);
            if(itrm1==itr1)
                return (res1<res2)?res2:res1;
            else
                return profit[itr1]-decay[itrm1];
        }
};
