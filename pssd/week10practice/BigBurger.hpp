/*
 * =====================================================================================
 *
 *       Filename:  BigBurger.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/20/17 00:47:26
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
#include <map>

using namespace std;

class BigBurger{


public:
    int maxWait(vector<int> arrival,vector<int> service){
        int res = 0;
        int time = 0;
        for(int i=0;i<(int)arrival.size();i++){
            if(time>arrival[i]){
                res = max(res,time-arrival[i]);
                time = time + service[i];
            }else
                time = arrival[i] + service[i];
        }
        return res;
    }

};
