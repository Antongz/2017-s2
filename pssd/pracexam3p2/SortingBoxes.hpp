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
		if((int)red.size()==1)
			return -1;
		if((int)red.size()==2){
			if()
		}

		int res = 0;

		for(int i=0;i<(int)red.size;i++){
			int temp = 0;
			if(red[i]>=green[i]&&red[i]>=blue[i]){
				temp = green[i] + blue[i];
			}else if(green[i]>=red[i]&&green[i]>=blue[i]){
				temp = red[i] + blue[i];
			}else if(blue[i]>=green[i]&&blue[i]>=blue[i]){
				temp = green[i] + red[i];
			}
			res += temp;
		}



		return res;
	}




};

