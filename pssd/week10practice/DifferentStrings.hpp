/*
 * =====================================================================================
 *
 *       Filename:  DifferentStrings.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/17/17 15:08:32
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
#include <algorithm>
#include <vector>

using namespace std;

class DifferentStrings{

public:
    int minimize(string A,string B){
        int res = 10000;
        int pos = 0;
        for(int i=0;i<B.length();i++){
            int len = 0;
            for(int j=0;j<A.length();j++){
                if(A[j]!=B[i+j])
                    len++;
            }
            res = min(res,len);
            if(pos+A.length()==B.length())
                break;
        }
        return res;
    }
};
