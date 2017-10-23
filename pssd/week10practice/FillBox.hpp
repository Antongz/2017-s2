/*
 * =====================================================================================
 *
 *       Filename:  FillBox.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/23/17 21:19:04
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
#include <map>
#include <algorithm>

using namespace std;

class FillBox{

public:
    int minCubes(int length,int width,int height,vector<int> cubes){
        int v = length*width*height;
        int pos = (int)cubes.size()-1;
        int countPow = (int)cubes.size()-1;
        int res = 0;
        while(v>0&&pos>=0){
            int temp = pow2(pos);
            int comp = temp;
            temp = temp*temp*temp;
            if(comp<=length&&comp<=width&&comp<=height){
                for(int i=0;i<cubes[pos];i++){
                    if(v>=temp){
                        res++;
                        v -= temp;
                    }
                }
            }
            pos--;
            if(v==0)
                break;
        }

        if(v!=0)
            return -1;
        else
            return res;
    }

    int pow2(int size){
        int count = 1;
        for(int i=0;i<size;i++)
            count *= 2;
        return count;
    }

};
