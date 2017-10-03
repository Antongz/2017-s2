/*
 * =====================================================================================
 *
 *       Filename:  Thimbles.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/26/2017 07:51:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;
class Thimbles{

public:
    int thimbleWithBall(vector<string> swaps){
    //initially the target is in the first one
        char res = '1';
        int itr = 0;
        while(itr<(int)swaps.size()-1){
            char pos1 = swaps[itr][0];
            char pos2 = swaps[itr][2];
            if(res==pos1){
                res = pos2;
            }
            else if(res==pos2){
                res = pos1;
            }

            itr++;
        }
        int final = 1;
        switch (res) {
        case '1':
            final = 1;
            break;
        case '2':
            final = 2;
            break;
        case '3':
            final = 3;
            break;

        }
        return final;
    }


};

