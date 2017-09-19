/*
 * =====================================================================================
 *
 *       Filename:  VeryInterestingMovie.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/2017 11:43:14 PM
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
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

class VeryInterestingMovie{

public:
    int maximumPupils(vector<string> seats){
        int res = 0;
        int length = seats[0].length();
        for(int itr=0;itr<(int)seats.size();itr++){
            int i = 0;
            while(i<length){
                if(seats[itr][i]=='Y'){
                    i++;
                    res++;
                }
                i++;
            }
        }
        return res;
    }
};
