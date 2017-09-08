/*
 * =====================================================================================
 *
 *       Filename:  BlackAndWhiteSolitaire.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/08/2017 11:35:13 PM
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

using namespace std;

class BlackAndWhiteSolitaire{

    public:
        int minimumTurns(string cardFront){
            int bodd = 0;
            int beven = 0;
            int wodd = 0;
            int weven = 0;

            for(int i=0;i<(short)cardFront.length();i++){
                if(cardFront[i]=='B'){
                    if(i%2==0)
                        bodd++;
                    else
                        beven++;
                }
                if(cardFront[i]=='W'){
                    if(i%2==0)
                        wodd++;
                    else
                        weven++;
                }
            }
            int res = 0;
            if((bodd+weven==beven+wodd)&&bodd+beven!=0&&wodd+weven!=0)
                return 0;

            return (bodd+weven>beven+wodd)? beven+wodd:bodd+weven;


        }

};
