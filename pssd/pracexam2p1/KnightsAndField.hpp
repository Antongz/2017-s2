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

using namespace std;

typedef pair<int,int> ii;

class KnightsAndField{
	map<ii,int> M;


	public:
		int place(vector<string> place){
			int res = 0;
			int n = place.size();
			int m = place[0].length();
			int checkM = min(n,m);
			vector<int> count1;
			vector<int> count2;

			int count = 0;
			
			for(int i=0;i<n;i++){
				count = 0;
				for(int j=0;j<m;j++){
					if(place[i][j]=='X')
						count++;
				}
				count1.push_back(count);
			}
		
			for(int i=0;i<m;i++){
				count = 0;
				for(int j=0;j<n;j++){
					if(place[j][i]=='X')
						count++;
				}
				count2.push_back(count);
			}
			

			int sum1 = 0;
			int sum2 = 0;
			for(int i=0;i<(short)count1.size();i++)
				if(count1[i]!=0)
					sum1++;
			for(int i=0;i<(short)count2.size();i++)
				if(count2[i]!=0)
					sum2++;

			int check1 = n - sum1;
			int check2 = m - sum2;


			res = min(check1,check2);
			return res;
		}

};


