#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <ctype.h>
#include <math.h>
#include <queue>
#include <stack>

using namespace std;

class SortingBoxes{

public:
	int minOp(vector<int> red,vector<int> green,vector<int> blue){
		int gBox = 0;	int rBox = 0;	int bBox = 0;
		if((int)red.size()<=2)
			return -1;

		int res = 0;
		vector<int> count;
		count.push_back(0);
		count.push_back(0);
		count.push_back(0);
		int maxR = 0;	int maxR2 = 0;	int cR = red[0];
		int maxG = 0;	int maxG2 = 0;	int cG = green[0];
		int maxB = 0;	int maxB2 = 0;	int cB = blue[0];
		for(int i=0;i<(int)red.size();i++){
			if(red[i]>=cR){
				cR = red[i];
				maxR2 = maxR;
				maxR = i;
			}
			if(green[i]>=cG){
				cG = green[i];
				maxG2 = maxG;
				maxG = i;
			}
			if(blue[i]>=cB){
				cB = blue[i];
				maxB2 = maxB;
				maxB = i;
			}
			
		}

		for(int i=0;i<(int)red.size();i++){
			int temp = 0;
			if(red[i]>=green[i]&&red[i]>=blue[i]){
				temp = green[i] + blue[i];
				count[0]++;
			}else if(green[i]>=red[i]&&green[i]>=blue[i]){
				temp = red[i] + blue[i];
				count[1]++;
			}else if(blue[i]>=green[i]&&blue[i]>=red[i]){
				temp = green[i] + red[i];
				count[2]++;
			}
			res += temp;
		}

		vector<int> pos0;
		bool check = true;
		for(int i=0;i<(int)count.size();i++){
			if(count[i]==0)
				pos0.push_back(i);
		}

		if((int)pos0.size()==0){
			return res;

		}else{
			for(int i=0;i<(int)pos0.size();i++){
				//no red ball
				if(pos0[i]==0){
					res -= red[maxR];
					res += max(green[maxR],blue[maxR]);
				}
				//no green ball
				if(pos0[i]==1){
					res -= green[maxR];
					res += max(red[maxR],blue[maxR]);
				}
				if(pos0[i]==2){
					res -= blue[maxR];
					res += max(green[maxR],red[maxR]);
				}

			}


			return res;
		}
	}




};

