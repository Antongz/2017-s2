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

using namespace std;
class NiceOrUgly{
    bool test = false;

    public:
    string describe(string s){
        return check(s,0,0,0,0);
    }

    string check(string s,int itr,int vowels,int consonants,int question){
        while(itr<=(short)s.length()){
            if(vowels==3||consonants==5){
                return "UGLY";
            }
            if(itr==s.length()&&(question>=3||test==true)){
                return "42";
            }

            if(itr==s.length()){
                return "NICE";
            }

            if(s[itr]=='A'||s[itr]=='E'||s[itr]=='I'||s[itr]=='O'||s[itr]=='U'){
                consonants = 0;
                question = 0;
                vowels++;
            }else if(s[itr]=='?'){
                if(vowels==2){
                    if(itr+1<s.length())
                        test = true;
                    vowels = 0;
                    consonants++;
                }else if(consonants==4){
                    if(itr+1<s.length())
                        test = true;
                    consonants = 0;
                    vowels++;
                }else{
                    string checkP = "";
                    string checkN = "";
                    checkP = check(s,itr+1,vowels+1,0,question+1);
                    checkN = check(s,itr+1,0,consonants+1,question+1);
                    if(checkP==checkN&&checkP=="UGLY")
                        return "UGLY";
                    else if(checkP!=checkN||(checkN==checkP&&checkP=="42"))
                        return "42";
                    else
                        return "NICE";
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
