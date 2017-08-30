/*
 * =====================================================================================
 *
 *       Filename:  RunLengthEncoding.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/30/2017 09:33:53 PM
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

class RunLengthEncoding{

    public:
        string decode(string text){
            int itr = 0;
            string res = "";
            bool checkP = false;
            int time = 0;
            while(itr<(short)text.length()){
                if(checkP==false)
                    time = 0;

                if(res.length()>50)
                    return "TOO LONG";
                if(time>50)
                    return "TOO LONG";

                switch(text[itr]){
                    case '1':
                        checkP = true;
                        time = time*10+1;
                        break;
                    case '2':
                        checkP = true;
                        time = time*10+2;
                        break;
                    case '3':
                        checkP = true;
                        time = time*10+3;
                        break;
                    case '4':
                        checkP = true;
                        time = time*10+4;
                        break;
                    case '5':
                        checkP = true;
                        time = time*10+5;
                        break;
                    case '6':
                        checkP = true;
                        time = time*10+6;
                        break;
                    case '7':
                        checkP = true;
                        time = time*10+7;
                        break;
                    case '8':
                        checkP = true;
                        time = time*10+8;
                        break;
                    case '9':
                        checkP = true;
                        time = time*10+9;
                        break;
                    case '0':
                        checkP = true;
                        time = time*10+0;
                        break;

                    default:
                        if(checkP){
                            for(int i=0;i<time;i++)
                                res += text[itr];
                            checkP = false;
                        }else
                            res += text[itr];
                }
                itr++;
            }
            if(res.length()>50)
                return "TOO LONG";
            return res;

        }
};
