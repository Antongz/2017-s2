/*
 * =====================================================================================
 *
 *       Filename:  RockStar.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/26/2017 08:37:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>

using namespace std;


class RockStar{

public:
	int getNumSongs(int ff,int fs,int sf,int ss){
		int res = 0;
		if(ff>0||fs>0){
			res += ff;
			if(fs>0){
				fs--;
				res++;
				res += ss;
				if(sf>0){
					res++;
					sf--;
					res + 2*min(fs,sf);
				}

			}
		}else{
			res += ss;
			if(sf>0)
				res++;
		}
		return res;
	}
};
