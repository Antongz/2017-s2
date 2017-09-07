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
        int vowels = 0;
        int consonants = 0;
        int question = 0;
        int itr = 0;
        string res = "NICE";
        while(itr<=(short)s.length()){
            if(vowels==3||consonants==5)
                return "UGLY";
            if(itr==s.length())
                return res;
            if(s[itr]=='A'||s[itr]=='E'||s[itr]=='I'||s[itr]=='O'||s[itr]=='U'){
                consonants = 0;
                question = 0;
                vowels++;
            }else if(s[itr]=='?'){
                if(vowels==2){
                    res = "42";
                    vowels = 0;
                    consonants++;
                }else if(consonants==4){
                    res = "42";
                    consonants = 0;
                    vowels++;
                }else{
                    vowels++;
                    consonants++;
                    question++;
                }
            }else{
                vowels = 0;
                question = 0;
                consonants++;
            }
            itr++;
        }
    }


};
