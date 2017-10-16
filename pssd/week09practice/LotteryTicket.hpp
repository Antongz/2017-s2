/*
 * =====================================================================================
 *
 *       Filename:  LotteryTicket.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/16/17 11:17:48
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

class LotteryTicket{

public:
	string buy(int price,int b1,int b2,int b3,int b4){
		vector<int> test;
		test.push_back(b1);
		test.push_back(b2);
		test.push_back(b3);
		test.push_back(b4);
		sort(test.begin(),test.end());
		int tempR = price;
		int itr = 3;
		while(itr>=0){
			if(test[itr]>price)
				itr--;
			else
				tempR -= test[itr], itr--;

			if(tempR==0)
				break;
		}

		if(tempR==0)
			return "POSSIBLE";
		else
            return "IMPOSSIBLE";
	}

};
