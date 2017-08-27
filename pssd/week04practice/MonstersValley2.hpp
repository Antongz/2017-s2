/*
 * =====================================================================================
 *
 *       Filename:  MonstersValley2.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/27/2017 01:09:35 AM
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

class MonstersValley2{

    public:
        int minimumPrice(vector<int> dread,vector<int> price){

            return checkMin(0,0,dread,price);
        }

        int checkMin(int itr,int curD,vector<int> dread,vector<int> price){
            if(itr>=dread.size())
                return 0;
            if(curD<dread[itr])
                return price[itr]+checkMin(itr+1,curD+dread[itr],dread,price);
            else
                return min(price[itr]+checkMin(itr+1,curD+dread[itr],dread,price),
                           checkMin(itr+1,curD,dread,price));

        }
};
