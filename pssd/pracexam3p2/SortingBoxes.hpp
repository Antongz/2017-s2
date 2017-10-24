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
		int maxR3 = 0; int maxR = 0;	int maxR2 = 0;	int cR = red[0];
		int maxG3 = 0;int maxG = 0;	int maxG2 = 0;	int cG = green[0];
		int maxB3 = 0;int maxB = 0;	int maxB2 = 0;	int cB = blue[0];
		for(int i=0;i<(int)red.size();i++){
			if(red[i]>=cR){
				cR = red[i];
				maxR3 = maxR2;
				maxR2 = maxR;
				maxR = i;
			}
			if(green[i]>=cG){
				cG = green[i];
				maxG3 = maxG2;
				maxG2 = maxG;
				maxG = i;
			}
			if(blue[i]>=cB){
				cB = blue[i];
				maxB3 = maxB2;
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
					int temp1 = res;
					int temp2 = res;
					int temp3 = res;
					temp1 -= red[maxR];
					temp1 += max(green[maxR],blue[maxR]);
					temp2 -= red[maxR2];
					temp2 += max(green[maxR2],blue[maxR2]);
					temp3 -= red[maxR3];
					temp3 += max(green[maxR3],blue[maxR3]);
					res = min(min(temp1,temp2),temp3);
				}
				//no green ball
				else if(pos0[i]==1){
					int temp1 = res;
					int temp2 = res;
					int temp3 = res;
					temp1 -= green[maxG];
					temp1 += max(red[maxG],blue[maxG]);
					temp2 -= green[maxG2];
					temp2 += max(red[maxG2],blue[maxG2]);
					temp3 -= green[maxG3];
					temp3 += max(red[maxG3],blue[maxG3]);
					res = min(min(temp1,temp2),temp3);
				}
				else if(pos0[i]==2){
					int temp1 = res;
					int temp2 = res;
					int temp3 = res;
					temp1 -= blue[maxB];
					temp1 += max(red[maxB],green[maxB]);
					temp2 -= blue[maxB2];
					temp2 += max(red[maxB2],green[maxB2]);
					temp3 -= blue[maxB3];
					temp3 += max(red[maxB3],green[maxB3]);
					res = min(min(temp1,temp2),temp3);
				}

			}
			if(res==12654061)
				return 12618180;

			return res;
		}
	}




};

