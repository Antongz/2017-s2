#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

class Teleport{

	public:
	int bestPath(int xMe,int yMe,int xHome,int yHome,vector<string> test){
		int Xdiff = abs(xHome-xMe);
		int Ydiff = abs(yHome-yMe);
		const char space [2] = " ";
		vector<int> stX;
		vector<int> stY;
		vector<int> resX;
		vector<int> resY;
		int xPob = 0;	int yPob = 0;
		for(int i=0;i<test.size();i++){
			stX.push_back(stoi(strtok(test[i],space)));
			stY.push_back(stoi(strtok(NULL,space)));
			resX.push_back(stoi(strtok(NULL,space)));
			resY.push_back(stoi(strtok(NULL,space)));
		}

		int chose = 0;
		

		return Xdiff+Ydiff;
	}


};
