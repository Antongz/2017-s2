/*
 * =====================================================================================
 *
 *       Filename:  NiceOrUgly.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/05/2017 03:12:41 PM
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
#include <string.h>
#include <vector>

using namespace std;
class NiceOrUgly{
public:
    string describe(string s){
        int check = 0;
        int vowels = 0;
        int consonants = 0;
        int question = 0;
        int itr = 0;
        string res = "NICE";
        while(itr<=(short)s.length()){
            if((vowels==3||consonants==5)&&question==0)
                return "UGLY";
            if(vowels+question==3||consonants+question==5)
                res = "42";
            if(question>=3)
                res = "42";

            if(itr==s.length())
                return res;
            if(s[itr]=='A'||s[itr]=='E'||s[itr]=='I'||s[itr]=='O'||s[itr]=='U'){
                if(check<0){
                    check = 0;
                    question = 0;
                }
                check++;
                consonants = 0;
                vowels++;
            }else if(s[itr]=='?'){
                if(vowels==2){
                    res = "42";
                    vowels = 0;
                    consonants = 1;
                    check = -1;
                }else if(consonants==4){
                    check = 1;
                    res = "42";
                    consonants = 0;
                    vowels = 1;
                }else{
                    check = 0;
                    question++;
                }
            }else{
                if(check>0){
                    check = 0;
                    question = 0;
                }
                check--;
                vowels = 0;
                consonants++;
            }
            itr++;
        }
    }



};
