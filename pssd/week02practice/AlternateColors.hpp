/*
 * =====================================================================================
 *
 *       Filename:  AlternateColors.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/05/2017 10:50:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>


using namespace std;

class AlternateColors{
    public:
        string getColor(long r,long g,long b,long k){

            int color = currColor(r,g,b,k,0);
            if(color==1)
                return "RED";
            if(color==2)
                return "GREEN";
            if(color==3)
                return "BLUE";
        }

        int currColor(long r,long g,long b,long k,int help){
            int min = 0;
            if(r<=g&&r<=b){
                min = r;
                help = 1;
            }
            if(g<=b&&g<=r){
                min = g;
                help = 2;
            }

            if(b<=r&&b<=g){
                min = b;
                help = 3;
            }

            if(k<=3*min+help){
                if(k%3==1){
                    return 1;
                }
                if(k%3==2){
                    return 2;
                }
                if(k%3==0){
                    return 3;
                }
            }else{
                if(r==min){
                    if(g-min==0){
                        return 3;
                    }if(b-min==0){
                        return 2;
                    }return currColor2(g-min,b-min,k-3*(min-1)-1,help);
                }
                if(g==min){
                    if(r-min==0){
                        return 3;
                    }if(b-min==0){
                        return 1;
                    }return currColor2(b-min,r-min,k-3*(min-1)-2,help);
                }
                if(b==min){
                    if(r-min==0){
                        return 2;
                    }if(g-min==0){
                        return 1;
                    }return currColor2(r-min,g-min,k-3*(min-1)-3,help);
                }
            }
        }
        int currColor2(long a,long b,long k,int help){
            long min = 0;
            if(a<b){
                min = a;
            }else{
                min = b;
            }
            if(k<=2*min){
                if(k%2==1){
                    if(help==1)
                        return 2;
                    if(help==2)
                        return 3;
                    if(help==3)
                        return 1;
                }else{
                    if(help==1)
                        return 3;
                    if(help==2)
                        return 1;
                    if(help==3)
                        return 2;
                }
            }else{
                if(help==1){
                    if(a<b){
                        return 3;
                    }else{
                        return 2;
                    }
                }
                if(help==2){
                    if(a<b){
                        return 1;
                    }else{
                        return 3;
                    }
                }
                if(help==3){
                    if(a<b){
                        return 2;
                    }else{
                        return 1;
                    }
                }
            }
        }


};
