/*
 * =====================================================================================
 *
 *       Filename:  HouseBuilding.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/02/2017 07:59:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class HouseBuilding{

    public:
        int getMinimum(vector<string> area){
            vector<vector<int>> inputList;
            int length = 0;
            for(int i=0;i<(short)area.size();i++){
                vector<int> inputI;
                string text = area[i];
                for(int j=0;j<(short)area[i].length();j++){
                    switch(text[j]){
                        case '1':
                            inputI.push_back(1);
                            break;
                        case '2':
                            inputI.push_back(2);
                            break;
                        case '3':
                            inputI.push_back(3);
                            break;
                        case '4':
                            inputI.push_back(4);
                            break;
                        case '5':
                            inputI.push_back(5);
                            break;
                        case '6':
                            inputI.push_back(6);
                            break;
                        case '7':
                            inputI.push_back(7);
                            break;
                        case '8':
                            inputI.push_back(8);
                            break;
                        case '9':
                            inputI.push_back(9);
                            break;
                        case '0':
                            inputI.push_back(0);
                            break;
                    }

                }
                length = inputI.size();
                inputList.push_back(inputI);
            }
            cout << length << " " << inputList.size() << endl;
            //determine our lowest and highest square
            vector<int> occ = {0,0,0,0,0,0,0,0,0};
            int tempMin = 0;
            int tempMax = 1;
            for(int i=0;i<(short)occ.size();i++){
                occ[i] = findMin(inputList,inputList.size(),length,tempMin,tempMax);
                tempMin++;
                tempMax++;
            }
            int Min = occ[0];
            for(int i=0;i<(short)occ.size();i++){
                if(occ[i]<Min)
                    Min = occ[i];
            }
            return Min;
        }

        int findMin(vector<vector<int>> list,int size,int length,int Min,int Max){
            int res = 0;
            for(int i=0;i<size;i++){
                for(int j=0;j<length;j++){
                    if(list[i][j]!=Min&&list[i][j]!=Max){
                        int tempM = min(abs(list[i][j]-Min),abs(list[i][j]-Max));
                        res = res + tempM;
                    }
                }
            }
            return res;
        }

};
