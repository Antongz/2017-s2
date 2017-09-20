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
        int res = words.size();
        vector<string> dup;
        vector<int> dupPost;

        for(int i=0;i<(int)words.size();i++){
            string temp = words[i];
            for(int j=0;j<(int)words.size();j++){
                if(i==j)
                    ;
                else{
                    if(words[j].length()>temp.length()){
                        string comp = words[j].substr(0,(int)temp.length());
                        if(temp==comp){
                            res--;
                            break;
                        }
                    }else if(words[j]==temp){
                            bool check = true;
                            int k = 0;
                            for(k=0;k<(int)dup.size();k++){
                                if(words[j]==dup[k]){
                                    check = false;
                                    break;
                                }
                            }

                            if(check){
                                res--;
                                dup.push_back(temp);
                                dupPost.push_back(i);
                            }else if(check==false&&i<=dupPost[k])
                                res--;
                    }
                }
            }
        }
        return res;
    }
};
