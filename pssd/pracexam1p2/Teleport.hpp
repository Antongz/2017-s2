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
		string a,b,c,d;
		vector<int> stX;
		vector<int> stY;
		vector<int> resX;
		vector<int> resY;
		int xPob = 0;	int yPob = 0;
		for(int i=0;i<test.size();i++){
			for(int i=0;i<4;i++){
			 	a=strtok(test[i],space);
				b=strtok(NULL,space);
				c=strtok(NULL,space);
				d=strtok(NULL,space);
				stX.push_back(stoi(a));
				stY.push_back(stoi(b));
				resX.push_back(stoi(c));
				resY.push_back(stoi(d));
			}
		}
		bool check = false;
		int minDiff = Xdiff+Ydiff;
		int count = 0;
		int Begin = 0;
		for(int i=0;i<stX.size();i++){
			if(abs(stX[i]-xMe)+abs(stY[i]-yMe)<minDiff){
				minDiff = abs(stX[i]-xMe)+abs(stY[i]-yMe);
				count = i;
				Begin = 0;
				check = true;
			}
			if(abs(resX[i]-xMe)+abs(resY[i]-yMe)<minDiff){
				minDiff = abs(resX[i]-xMe)+abs(resY[i]-yMe);
				count = i;
				Begin = 1;
				check = true;
			}
		}

		int compare = 0;
		if(check){
			if(Begin==0){
				compare = abs(stX[count]-xMe)+abs(stY[count]-yMe) + 10 + abs(resX[count]-xHome)+abs(resY[count]-yHome);
			}
			if(Begin==1){                                                                           
                  compare = abs(stX[count]-xHome)+abs(stY[count]-yHome) + 10 + abs(resX[count]-xMe)+abs(resY[count]-yMe);                                                                                           }  
		
		}
		


		int chose = 0;
		
		if(compare<=Xdiff+Ydiff)
			return compare;

		return Xdiff+Ydiff;
	}


};

/*
int main(){
	Teleport test;
	vector<string> t;
	t.push_back("1000 1001 1000 1002");
	t.push_back("1000 1003 1000 1004");
	t.push_back("1000 1005 1000 1006");
	test.bestPath(3,3,4,5,t);
	
	return 0;
}
*/
