/*
 * =====================================================================================
 *
 *       Filename:  RGBStreet.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/29/2017 03:12:24 PM
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
#include <string>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>

using namespace std;

class RGBStreet{
    const char space[2] = " ";

    public:
        int estimateCost(vector<string> houses){
            vector<vector<int>> house;

            for(int i=0;i<houses.size();i++){
                vector<int> tmp;
                char *temp = new char [houses[i].length()+1];
                strcpy(temp,houses[i].c_str());
                tmp.push_back(stoi(strtok(temp,space)));
                tmp.push_back(stoi(strtok(NULL,space)));
                tmp.push_back(stoi(strtok(NULL,space)));
                house.push_back(tmp);
            }

            int res = estimate(-1,0,house);
            return res;
        }


        int estimate(int help,int itr,vector<vector<int>> tmp){
            if(itr==tmp.size())
                return 0;
            else{
                if(help==0)
                    return min(tmp[itr][1]+estimate(1,itr+1,tmp),tmp[itr][2]+estimate(2,itr+1,tmp));
                else if(help==1)
                    return min(tmp[itr][0]+estimate(0,itr+1,tmp),tmp[itr][2]+estimate(2,itr+1,tmp));
                else if(help==2)
                    return min(tmp[itr][1]+estimate(1,itr+1,tmp),tmp[itr][0]+estimate(0,itr+1,tmp));
                else
                    return min(min(tmp[itr][0]+estimate(0,itr+1,tmp),tmp[itr][1]+estimate(1,itr+1,tmp)),tmp[itr][2]+estimate(2,itr+1,tmp));

            }
        }

};
