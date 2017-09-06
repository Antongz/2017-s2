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
    public:
        string describe(string s){
            return check(s,0,0,0);
        }

        string check(string s,int itr,int vowels,int consonants){
            if(vowels==3||consonants==5)
                return "UGLY";
            if(itr==s.length())
                return "NICE";
            if(s[itr]=='?'){
                string checkP = "";
                string checkN = "";
                checkP = check(s,itr+1,vowels+1,0);
                checkN = check(s,itr+1,0,consonants+1);
                if(checkP==checkN&&checkP=="UGLY")
                    return "UGLY";
                else if(checkP!=checkN)
                    return "42";
                else
                    return "NICE";
            }
            else if(s[itr]=='A'||s[itr]=='E'||s[itr]=='I'||s[itr]=='O'||s[itr]=='U')
                return check(s,itr+1,vowels+1,0);
            else
                return check(s,itr+1,0,consonants+1);

        }


};
