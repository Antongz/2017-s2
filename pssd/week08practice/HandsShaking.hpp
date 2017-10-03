/*
 * =====================================================================================
 *
 *       Filename:  HandsShaking.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/02/2017 03:56:18 PM
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
#include <map>

using namespace std;

class HandsShaking{

public:
    long long countPerfect(int n){
        int tempN = n/2;
        long long res = 0;
        res = fac(2*tempN)/(fac(tempN+1)*fac(tempN));
        return res;
    }
    long long fac(int n){
        long long res = 1;
        while(n>=1){
            res = res*n;
            n--;
        }
        return res;
    }

};
