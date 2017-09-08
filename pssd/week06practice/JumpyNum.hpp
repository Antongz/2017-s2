/*
 * =====================================================================================
 *
 *       Filename:  JumpyNum.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/07/2017 11:33:10 PM
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

typedef vector<int> vi;
typedef pair<int,int>ii;
typedef long long ll;

class JumpyNum{
   map<ii,int> M;

public:
    int howMany(int low,int high){
        return calc(high)-calc(low-1);
    }

    int calc(int num){
        int res = 0;
        for(int i=0;i<=9;i++)
            res += solve(num,i);
        return res;
    }

    int solve(int low,int high){
        if(low==0||high>low)
            return 0;
        if(M.find(ii(low,high))!=M.end())
            return M[ii(low,high)];
        int res = (high != 0);

        for(int i=0;i<=9;i++)
            if(abs(i-high)>=2)
                res += solve((low-high)/10,i);
        M[ii(low,high)] = res;
        return res;
    }
};

