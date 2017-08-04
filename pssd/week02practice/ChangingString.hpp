/*
 * =====================================================================================
 *
 *       Filename:  ChangingString.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/02/2017 10:43:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;


class ChangingString{

    public:
        int distance(string A,string B,int k){
            int res = 0;
            vector<int> diff;
            for(int i=0;i<A.length();i++){
                char a = A[i];
                char b = B[i];
                diff.push_back(abs(a-b));
            }

            int temp = 0;
            //sort our diff list
            for(int i=0;i<diff.size();i++){
                for(int j=i+1;j<diff.size();j++){
                    if(diff[j]>diff[i]){
                        temp = diff[j];
                        diff[j] = diff[i];
                        diff[i] = temp;
                    }
                }
            }

            //change k character
            for(int i=0;i<diff.size();i++){
                if(k>0){
                    if(diff[i]==0){
                        diff[i] = 1;
                    }else{
                        diff[i] = 0;
                    }
                    k--;
                }

                res += diff[i];
            }
            return res;
        }

};

