/*
 * =====================================================================================
 *
 *       Filename:  SimpleCompressor.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/14/2017 10:40:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

class SimpleCompressor{
    int n = 0;

    public:
        string uncompress(string data){
            string res="";
            string ins = "";
            string inc = "";
            bool check=true;
            int itr=0;
            int n=1;
            int temp=0;
            while(check){
                if(data[itr]!='['&&data[itr]!=']')
                    res+=data[itr];
                if(data[itr]=='['){
                    while(data[itr]!=']'){
                        if(data[itr]=='['){
                            itr++;
                            ins = data[itr];
                            temp = stoi(ins);
                            n *= temp;
                        }else{
                            inc += data[itr];
                        }
                        itr++;
                    }
                    //data[itr] should be "]"
                    if(data[itr]==']'){
                        while(data[itr]==']'){
                           itr++;
                        }
                        for(int i=0;i<n;i++)
                            res += inc;

						if(itr+1 != data.length())
							itr++;
                    }
                }else{
                    itr++;
                }
                if(itr>=data.length())
                    check=false;
            }

            return res;
        }

};