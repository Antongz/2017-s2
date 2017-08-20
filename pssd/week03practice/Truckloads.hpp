/*
 * =====================================================================================
 *
 *       Filename:  Truckloads.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/12/2017 05:50:08 PM
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

class Truckloads{

    public:
        int numTrucks(int numCrates,int loadSize){
            if(numCrates<=loadSize)
                return 1;
            else{
                return numTrucks(numCrates/2,loadSize)+numTrucks(numCrates-numCrates/2,loadSize);
            }
        }



};
