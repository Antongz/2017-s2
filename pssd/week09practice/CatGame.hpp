/*
 * =====================================================================================
 *
 *       Filename:  CatGame.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/08/2017 09:42:51 PM
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
#include <string>
#include <string.h>

using namespace std;

class CatGame{

public:
    int getNumber(vector<int> coordinates,int X){
        if((int)coordinates.size()==1){
            return 0;
        }
        int minV = coordinates[0];
        int sminV = coordinates[0];
        int maxV = coordinates[0];
        int smaxV = coordinates[0];
        for(int i=0;i<(int)coordinates.size();i++){
            if(coordinates[i]<minV){
                sminV = minV;
                minV = coordinates[i];
            }
            if(coordinates[i]>maxV){
                smaxV = maxV;
                maxV = coordinates[i];
            }
        }

        vector<int> countN;
        for(int i=0;i<(int)coordinates.size();i++){
            if(coordinates[i]!=minV&&coordinates[i]!=maxV){
                int tempD = (abs((minV+X)-(coordinates[i]-X))<abs((maxV-X)-(coordinates[i]+X)))? (coordinates[i]-X):(coordinates[i]+X);
                countN.push_back(tempD);
            }else{
                if(coordinates[i]==minV)
                    countN.push_back(minV+X);
                else
                    countN.push_back(maxV-X);
            }
        }
        int tempM = countN[0];
        int tempm = countN[0];
        for(int i=0;i<(int)countN.size();i++){
            if(countN[i]>tempM)
                tempM = countN[i];
            if(countN[i]<tempm)
                tempm = countN[i];
        }
        //cout << tempM << " " << tempm << endl;
        return abs(tempM-tempm);
    }

};
