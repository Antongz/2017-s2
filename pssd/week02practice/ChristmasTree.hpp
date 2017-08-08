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
			if(red+green+blue<sum)
				return 0;
			else{
                return count(red,green,blue,N); 
			}
		}

		long count(int red,int green,int blue,int layer){
            int redR = red;
			int greenR = green;
			int blueR = blue;
            long res = 0;
			
			if(red+green+blue<layer||red<0||green<0||blue<0)
				return 0;
			if(layer==1){
				if(red>0)
					res++;
				if(green>0)
					res++;
				if(blue>0)
					res++;

                return res;
            }else{
				//when the layer is not equay to the first one
                if(layer%3==0){
                //this could have 3! choices
                    if(red>=layer||green>=layer||blue>=layer)
                        return count(red-layer,green,blue,layer--)+count(red,green-layer,blue,layer--)+count(red,green,blue-layer,layer--);
                    
                    return count(red-layer/3,green-layer/3,blue-layer/3,layer--);
                }
                if(layer%3==1||layer%3==2){
                    if(layer%2==0)
                        return count(red-layer/2,green-layer/2,blue,layer--)+count(red-layer/2,green,blue-layer/2,layer--)+count(red,green-layer/2,blue-layer/2,layer--);
                   return count(red-layer,green,blue,layer--)+count(red,green-layer,blue,layer--)+count(red,green,blue-layer,layer--);

                }	
			}

		}
	

};
