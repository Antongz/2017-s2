/*
 * =====================================================================================
 *
 *       Filename:  ProblemsToSolve.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/27/2017 08:34:51 PM
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
#include <map>
#include <algorithm>

using namespace std;

class ProblemsToSolve{

public:
    int minNumber(vector<int> pleasantness,int variety){
        int res = pleasantness.size();
        //bool checkFirst = true;

        for(int i=0;i<(int)pleasantness.size();i++){
            int temp = pleasantness[i];
            bool checkFind = false;
            for(int j=i+1;j<(int)pleasantness.size();j++){
                if(abs(temp-pleasantness[j])>=variety){
                    int tempR;
                    if(i%2==0&&j%2==0){
                        tempR = (j-i)/2 + 1;
                    }else if(i%2==0&&j%2!=0){
                        tempR = (i/2) + 1 + (j-i)/2 + 1;
                    }else if(i%2!=0&&j%2==0){
                        tempR = (i/2) + 2 + (j-i)/2 + 1;
                    }else{
                        //i%2!=0&&j%2!=0
                        tempR = (i/2) + 2 + (j-i)/2;
                    }


                    if(res>tempR){
                        res = tempR;
                        checkFind = false;
                    }
                    break;

                }
            }
            if(checkFind)
                ;//res++;
        }
        return res;
    }

};
