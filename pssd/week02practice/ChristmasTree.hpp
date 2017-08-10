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
                //cout << "0 here" << endl;
                return 0;
            }else{
                if(N==1&&red>=0&&green>=0&&blue>=0){
                    long res = 0;
                    if(red>0){
                        //cout << "red ";
                        res++;
                    }
                    if(green>0){
                       // cout << "green ";
                        res++;
                    }
                    if(blue>0){
                       // cout << "blue ";
                        res++;
                    }
                   // cout << "return res: " << res << endl;
                    return res;
                }else{
                    if(N%3==0&&N%2!=0){
                        int mul3 = 1;
                        int div3 = 1;
                        for(int i=N/3+1;i<=N;i++){
                            mul3 = mul3*(i);
                        }
                        for(int i=1;i<=2*N/3;i++){
                            div3 = div3*i;
                        }//cout<< "mul3/div3: " << mul3/div3 << endl;;

                        int mul2 = 1;
                        int div2 = 1;
                        for(int i=N/3+1;i<=2*N/3;i++){
                            mul2 = mul2*(i);
                            div2 = div2*(i-N/3);
                        }
                        //cout << "mul2/div2: " << mul2/div2 << endl;

                        return decorationWays(N-1,red-N,green,blue)+decorationWays(N-1,red,green-N,blue)+decorationWays(N-1,red,green,blue-N)+(mul3/div3)*(mul2/div2)*decorationWays(N-1,red-N/3,green-N/3,blue-N/3);
                    }
                    else if(N%2==0&&N%3!=0){
                        int mul = 1;
                        int div = 1;
                        for(int i=N/2+1;i<=N;i++){
                            mul = mul*(i);
                            div = div*(i-N/2);
                        }
                        return (mul/div)*decorationWays(N-1,red-N/2,green-N/2,blue)+(mul/div)*decorationWays(N-1,red-N/2,green,blue-N/2)+(mul/div)*decorationWays(N-1,red,green-N/2,blue-N/2)
                                +decorationWays(N-1,red-N,green,blue)+decorationWays(N-1,red,green-N,blue)+decorationWays(N-1,red,green,blue-N);
                    }
                    else if(N%2==0&&N%3==0){
                        int mul3 = 1;
                        int div3 = 1;
                        for(int i=N/3+1;i<=N;i++){
                            mul3 = mul3*(i);
                        }
                        for(int i=1;i<=2*N/3;i++){
                            div3 = div3*i;
                        }//cout<< "mul3/div3: " << mul3/div3 << endl;;

                        int mul2 = 1;
                        int div2 = 1;
                        for(int i=N/3+1;i<=2*N/3;i++){
                            mul2 = mul2*(i);
                            div2 = div2*(i-N/3);
                        }

                        int mul = 1;
                        int div = 1;
                        for(int i=N/2+1;i<=N;i++){
                            mul = mul*(i);
                            div = div*(i-N/2);
                        }

                        return decorationWays(N-1,red-N,green,blue)+decorationWays(N-1,red,green-N,blue)+decorationWays(N-1,red,green,blue-N)+(mul3/div3)*(mul2/div2)*decorationWays(N-1,red-N/3,green-N/3,blue-N/3)+
                                (mul/div)*decorationWays(N-1,red-N/2,green-N/2,blue)+(mul/div)*decorationWays(N-1,red-N/2,green,blue-N/2)+(mul/div)*decorationWays(N-1,red,green-N/2,blue-N/2);
                    }

                    else{
                        return decorationWays(N-1,red-N,green,blue)+decorationWays(N-1,red,green-N,blue)+decorationWays(N-1,red,green,blue-N);
                    }
                }
            }
        }

};
