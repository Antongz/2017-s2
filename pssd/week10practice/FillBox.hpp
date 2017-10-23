/*
 * =====================================================================================
 *
 *       Filename:  FillBox.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/23/17 21:19:04
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
#include <map>
#include <algorithm>
#include <math.h>

using namespace std;

class FillBox{

public:
    int minCubes(long long length,long long width,long long height,vector<int> cubes){
        long long done = 0;
        int res = 0;
        for(int i=(int)cubes.size()-1;i>=0;i--){
            done *= 8;
            long long x = (1LL<<i);
            long long t = (length/x)*(width/x)*(height/x) - done;
            long long take = min(t,(long long)cubes[i]);
            done += take;
            res += take;
        }
        return (done==length*width*height? res:-1);
    }

};
