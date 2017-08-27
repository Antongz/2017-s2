/*
 * =====================================================================================
 *
 *       Filename:  ImportantTasks.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/22/2017 03:18:49 PM
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

class ImportantTasks{
	
	public:
        int maximalCost(vector<int> complexity, vector<int> computers){
            int res = 0;
            sort(complexity.begin(),complexity.end());
            sort(computers.begin(),computers.end());

            int itr1 = complexity.size()-1;
            int itr2 = computers.size()-1;
            while(itr1>=0){
                if(computers[itr2]>=complexity[itr1])
                    itr2--;
                itr1--;
            }

            res = computers.size() - itr2 - 1;
            return res;
        }

};
