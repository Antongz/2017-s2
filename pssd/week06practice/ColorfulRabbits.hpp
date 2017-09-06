/*
 * =====================================================================================
 *
 *       Filename:  ColorfulRabbits.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/05/2017 02:15:20 PM
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

class ColorfulRabbits{

    public:
        int getMinimum(vector<int> replies){
            int res = 0;
            vector<vector<int>> list;
            vector<int> colors;
            vector<int> count;
            bool check = false;
            for(int i=0;i<(short)replies.size();i++){
                int num = replies[i];
                check = true;
                for(int j=0;j<(short)count.size();j++){
                    if(colors[j]==num&&count[j]<colors[j]+1){
                        check = false;
                        count[j]++;
                        break;
                    }
                }

                if(check){
                    colors.push_back(num);
                    count.push_back(1);
                }
            }

            for(int i=0;i<(short)colors.size();i++){
                if(count[i]!=colors[i]+1)
                    res += colors[i] + 1;
                else
                    res += count[i];
            }

            return res;
        }
};
