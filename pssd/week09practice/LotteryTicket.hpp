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
        vector<int> count;
        for(int i=0;i<4;i++){
            int temp = test[i];
            count.push_back(test[i]);
            for(int j=i+1;j<4;j++){
                temp += test[j];
                count.push_back(test[i]+test[j]);
                count.push_back(temp);
            }
            if(i<2)
                count.push_back(temp-test[i+1]);
        }
        for(int i=0;i<(int)count.size();i++){
            //cout << count[i] << " ";
            if(count[i]==price)
                return "POSSIBLE";
        };cout << endl;
        return "IMPOSSIBLE";
    }

};
