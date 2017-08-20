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
            bool checkS = false;
			int itr=0;
			int n=0;
            int numBrac=0;
            int temp=0;
			while(check){
				res+=data[itr];
				if(data[itr]=="["){
                    numBrac++;
                    checkS = true;
                    while(checkS==true){
                        itr++;  //it should be an int
                        ins = data[itr];
                        temp = stoi(data[itr]);
                        n = temp;
                        itr++;  //could be int or bracket
                        if(data[itr]=="["){
                            while(data[itr]!="]"){
                                if(data[itr]=="["){
                                    itr++;
                                    ins = data[itr];
                                    temp = stoi(data[itr]);
                                    n *= temp;
                                }else{
                                    while(data[itr]!="]"){
                                        inc += data[itr];
                                    }
                                }
                                itr++;
                            }
                            //data[itr] should be "]"
                            while(data[itr]=="]"){
                                numBrac--;
                                itr++;
                            }
                            for(int i=0;i<n;i++)
                                res += inc;
                        }
                        if(numBrac==0)
                            checkS = false;
                    }
				} 
                if(itr==data.length()){
                    check=false;
                    break;
                }
				itr++;
				if(itr==data.length())
					check=false;
			}			

            return res;
		}

};
