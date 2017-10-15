/*
 * =====================================================================================
 *
 *       Filename:  CellRemoval.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/12/17 01:13:36
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

class CellRemoval{
    int n = 0;
    int killed = 0;
    vector<int> test[51];
    int search(int v){
        if(v==killed)
            return 0;
        if(test[v].empty())
            return 1;
        int x = 0;
        for(int i=0;i<(int)test[v].size();i++)
            x += search(test[v][i]);
        return x;
    }

public:
	int remainingCell(vector<int> parent,int deletedCell){
        killed = deletedCell;
        n = (int)parent.size();
        int root = 0;
        for(int i=0;i<(int)parent.size();i++)
            if(parent[i]==-1)
                root = i;
            else
                test[parent[i]].push_back(i);
        return search(root);
	} 


};
