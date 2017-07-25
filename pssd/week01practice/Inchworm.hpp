/*
 * =====================================================================================
 *
 *       Filename:  lnchworm.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/2017 09:36:55 PM
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

class Inchworm{
	public:
		int lunchtime(int branch, int rest, int leaf){
			int res = 1;
			int travelP = rest;
			while(travelP<=branch){
				if(travelP%leaf==0)
					res++;

				travelP += rest;
			}			

			return res;		//return result
		}
};



