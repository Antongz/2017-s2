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
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <map>

using namespace std;


class HandsShaking{
    long long dp[51];
    long long find(int n){
        if(n==0)
            return 1;
        if(dp[n]!=-1)
            return dp[n];
        dp[n] = 0;
        for(int i=1;i<n;i++)
            dp[n] += find(i-1)*find(n-1-i);

        return dp[n];
    }

public:
    long long countPerfect(int n){
        memset(dp,0xff,sizeof(dp));
        return find(n);
    }
    long long fac(int n,int start){
        long long res = 1;
        while(n>=start){
            res = res*n;
            n--;
        }
        return res;
    }

};
