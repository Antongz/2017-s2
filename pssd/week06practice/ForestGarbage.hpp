/*
 * =====================================================================================
 *
 *       Filename:  ForestGarbage.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/06/2017 11:24:59 PM
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
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <map>

using namespace std;



class ForestGarbage{

    int wei[50][50];
    int d[50][50];
    bool marked[50][50];
    int m = 0;
    int n = 0;

    public:
        vector<int> bestWay(vector<string> forest){
            n = forest.size();
            m = forest[0].size();
            int finalX = 0;
            int finalY = 0;
            int curX = 0;
            int curY = 0;
            memset(wei,0,sizeof(wei));
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(forest[i][j]=='g'){
                        wei[i][j] = 10000;
                    }else if((forest[i][j]=='.')&&((i+1<n&&forest[i+1][j]=='g')||(i>0&&forest[i-1][j]=='g')||
                                                   (j+1<m&&forest[i][j+1]=='g')||(j-1>0&&forest[i][j-1]=='g'))){
                        wei[i][j] = 1;
                    }else if(forest[i][j]=='F'){
                        finalX = i;
                        finalY = j;
                    }else if(forest[i][j]=='S'){
                        curX = i;
                        curY = j;
                    }
                }
            }

            dij(curX,curY);
            vector<int>res;
            res.push_back(d[finalX][finalY]/10000);
            res.push_back(d[finalX][finalY]%10000);
            return res;
            //return result;
        }

        void findBest(int curX,int curY){
            memset(d,-1,sizeof(d));
            memset(marked,0,sizeof(marked));
            d[curX][curY] = 0;
            while(curX!=-1){
                marked[curX][curY] = 1;
                if(curX>0&&(d[curX][curY]+wei[curX-1][curY]<d[curX-1][curY]||d[curX-1][curY]==-1))
                    d[curX-1][curY] = d[curX][curY] + wei[curX-1][curY];
                if(curX<n-1&&(d[curX][curY]+wei[curX+1][curY]<d[curX+1][curY]||d[curX+1][curY]==-1))
                    d[curX+1][curY] = d[curX][curY] + wei[curX+1][curY];
                if(curY>0&&(d[curX][curY]+wei[curX][curY-1]<d[curX][curY-1]||d[curX][curY-1]==-1))
                    d[curX][curY-1] = d[curX][curY] + wei[curX][curY-1];
                if(curY<m-1&&(d[curX][curY]+wei[curX][curY+1]<d[curX][curY+1]||d[curX][curY+1]==-1))
                    d[curX][curY+1] = d[curX][curY] + wei[curX][curY+1];

                curX = curY = -1;
                for(int i=0;i<n;i++)
                    for(int j=0;j<m;j++)
                        if(d[i][j]!=-1&&!marked[i][j]&&(curX==-1||d[i][j]<d[curX][curY]))
                            curX = i, curY = j;
            }
        }


};
