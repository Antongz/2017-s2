/*
 * =====================================================================================
 *
 *       Filename:  SimpleDuplicateRemover.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/29/2017 03:09:13 PM
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
#include <vector>
#include <algorithm>

using namespace std;
class SimpleDuplicateRemover{


    public:
        vector<int> process(vector<int> sequence){
            vector<int> res;
            bool checkD = true;
            for(int i=0;i<(short)sequence.size();i++){
                checkD = true;
                for(int j=i+1;j<(short)sequence.size();j++){
                    if(sequence[j]==sequence[i]){
                        checkD = false;
                        break;
                    }
                }
                if(checkD)
                    res.push_back(sequence[i]);
            }
            //reverse(res.begin(),res.end());
            return res;
        }
};
