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
class WordGame{

public:
	int bestScore(string S){
		vector<int> count;
		vector<char> charC;

		for(int i=0;i<(int)S.length();i++){

			bool check = true;
			for(int j=0;j<(int)charC.size();j++){
				if(charC[j]==S[i]){
					check = false;
					count[j]++;
					break;
				}

			}
			if(check){
				charC.push_back(S[i]);
				count.push_back(1);
			}
		}

		int res = 0;
		sort(count.begin(),count.end());
		reverse(count.begin(),count.end());
		res = square(count[0]+count[1]);
		for(int i=2;i<(int)count.size();i++)
			res += square(count[i]);


		return res;

	}

	int square(int x){
		return x*x;
	}


};
