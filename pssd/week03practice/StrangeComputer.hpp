/*
 * =====================================================================================
 *
 *       Filename:  StrangeComputer.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/18/2017 01:14:43 PM
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


class StrangeComputer{

    public:
        int setMemory(string mem){
            int res = 0;
            int index = 0;
            char checkP;
            while(index<mem.length()){
                if(index==0){
                    if(mem[index]=='1')
                        res++;
                }
                if(index>0){
                    if(mem[index]!=checkP)
                        res++;
                }

                checkP = mem[index];
                index++;
            }

            return res;
        }


};
