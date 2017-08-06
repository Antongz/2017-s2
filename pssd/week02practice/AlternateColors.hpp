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

			int color = currColor(r,g,b,k,1);
			if(color==1)
				return "RED";
			if(color==2)
				return "GREEN";
			if(color==3)
				return "BLUE";
		}

		int currColor(long r,long g,long b,long k,int help){
			if(k==1)
				return help;
			else{
				if(help==1){
					if(g>0)
						return currColor(r-1,g,b,k-1,2);
					else if(g==0&&b>0)
						return currColor(r-1,g,b,k-1,3);
					else
                        return 1;
						
				}
				if(help==2){
					if(b>0)
						return currColor(r,g-1,b,k-1,3);
					else if(b==0&&a>0)
						return currColor(r,g-1,b,k-1,1);
					else
                        return 2;
				}
				if(help==3){
                    if(r>0)
						return currColor(r,g,b-1,k-1,1);
					else if(a==0&&g>0)
						return currColor(r,g,b-1,k-1,2);
					else
                        return 3;
				}
							
			}

		}


};
