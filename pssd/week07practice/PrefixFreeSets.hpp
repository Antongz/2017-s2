/*
 * =====================================================================================
 *
 *       Filename:  PrefixFreeSets.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/19/2017 06:12:54 PM
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

using namespace std;
class PrefixFreeSets{
public:
    int maxElements(vector<string> words){
        vector<string> uniqueSet;
        uniqueSet.push_back(words[0]);
        for(int i=1;i<(int)words.size();i++){
            bool check = true;
            for(int j=0;j<i;j++){
                if(words[j]==words[i])
                    check = false;
            }
            if(check)
                uniqueSet.push_back(words[i]);
        }
        int res = uniqueSet.size();

        for(int i=0;i<(int)uniqueSet.size();i++){
            string temp = uniqueSet[i];
            for(int j=0;j<(int)uniqueSet.size();j++){
                if(i==j)
                    ;
                else{
                    if(uniqueSet[j].length()>temp.length()){
                        string comp = uniqueSet[j].substr(0,(int)temp.length());
                        if(temp==comp){
                            res--;
                            break;
                        }
                    }
                }
            }
        }
        return res;
    }
};
