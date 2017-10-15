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
#include <queue>

using namespace std;

class CellRemoval {
  int N = 0;
  vector<bool> ch,m;
 public:
  int cellsLeft(vector<int> parent, int deletedCell) {
    N = (int)parent.size();
    ch.resize(N);
    m.resize(N);
    for(int i=0;i<N;i++)
        ch[i]=m[i]=false;
    queue<int> q;
    for(int i=0;i<N;i++)
        if(parent[i]==-1){
            ch[i] = true;
            q.push(i);
            break;
        }

    while(!q.empty()){
      int t = q.front();
      q.pop();
      if(t==deletedCell){
          ch[t] = false;
          continue;
      }
      for(int i=0;i<N;i++){
        if(parent[i]==t){
            m[t]=true;
            ch[i]=true;
            q.push(i);
        }
      }
    }
    int cnt=0;
    for(int i=0;i<N;i++)
        if(ch[i]==true&&m[i]==false)
            cnt++;
    return cnt;
  }
};
