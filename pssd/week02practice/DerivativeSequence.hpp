/*
 * =====================================================================================
 *
 *       Filename:  DerivativeSequence.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/04/2017 09:23:39 PM
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


using namespace std;


class DerivativeSequence{


	public:
		vector<int> derSeq(vector<int> a,int n){
			vector<int> res;
			if(n==0)
				return a;
			else{
				for(int i=1;i<a.size();i++){
					res.push_back(a[i]-a[i-1]);
				}		
				return derSeq(res,n-1);
			}
		}

};
