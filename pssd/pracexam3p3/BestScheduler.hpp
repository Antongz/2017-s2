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

class BestScheduler{

public:
	int minTime(vector<int> time,vector<string> prec){

		int maxT = 0;
		for(int i=0;i<(int)time.size();i++)
			maxT = max(maxT,time[i]);
		int res = 0;
		for(int i=0;i<(int)prec.size();i++){

			for(int j=0;j<(int)prec[0].length();j++){
				if(prec[j]=='Y')
					res += time[j];

			}
		}

		return maxT;
	}

};

