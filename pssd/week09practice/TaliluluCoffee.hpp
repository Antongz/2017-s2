/*
 * =====================================================================================
 *
 *       Filename:  TaliluluCoffee.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/15/17 21:31:07
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
#include <algorithm>

using namespace std;

class TaliluluCoffee{

public:
	int maxTip(vector<int> tips){
		sort(tips.begin(),tips.end());
		int res = 0;
		int itr = 0;
		while(true){
			bool check = true;
			itr = 0;
			for(int i=0;i<(int)tips.size();i++){
				if(tips[i]!=0&&check){
					itr = i;
					res += tips[i];
					tips[i] = 0;
					check = false;
				}else if(tips[i]!=0&&check==false){
					tips[i]--;
				}				
			}
			if(check)
				break;
		}
		return res;
	}
};
