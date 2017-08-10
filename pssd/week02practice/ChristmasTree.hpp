/*
 * =====================================================================================
 *
 *       Filename:  ChristmasTree.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/05/2017 09:58:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <math.h>



using namespace std;

class ChristmasTree{
    public:
        long decorationWays(int N,int red,int green,int blue){
            int sum = 0;
            for(int i=1;i<=N;i++){
                sum += i;
            }
            if(red+green+blue<sum||red<0||green<0||blue<0){
                return 0;
            }else{
                if(N==1){
                    long res = 0;
                    if(red>0)
                        res++;
                    if(green>0)
                        res++;
                    if(blue>0)
                        res++;

                    return res;
                }else{
                    if(N%3==0&&N%2!=0){
                        return decorationWays(N-1,red-N,green,blue)+decorationWays(N-1,red,green-N,blue)+decorationWays(N-1,red,green,blue-N)+decorationWays(N-1,red-N/3,green-N/3,blue-N/3);
                    }
                    if(N%2==0&&N%3!=0){
                        return decorationWays(N-1,red-N/2,green-N/2,blue)+decorationWays(N-1,red-N/2,green,blue-N/2)+decorationWays(N-1,red,green-N/2,blue-N/2)+decorationWays(N-1,red-N,green,blue)+decorationWays(N-1,red,green-N,blue)+decorationWays(N-1,red,green,blue-N);
                    }

                    return decorationWays(N-1,red-N,green,blue)+decorationWays(N-1,red,green-N,blue)+decorationWays(N-1,red,green,blue-N);
                }
            }
        }

};
