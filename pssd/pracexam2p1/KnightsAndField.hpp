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

			int count = 0;
			for(int i=0;i<n;i++){
				count = 0;
				for(int j=0;j<m;j++){
					if(place[i][j]=='X')
						count++;
				}

				if(count==0)
					res++;
			}

			return res;
		}

};


