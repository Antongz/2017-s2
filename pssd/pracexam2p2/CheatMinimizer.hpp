#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <ctype.h>

using namespace std;

typedef pair<int,int> ii;

class CheatMinimizer{
	map<ii,int> M;

	public:
		int minimize(vector<int>ratings,int yourRating){
			int res = 0;
			vector<int> results;
			for(int i=0;i<ratings.size();i++)
				results.push_back(findPlace(ratings,yourRating,i));

			res = results[0];
			for(int i=0;i<results.size();i++){
				if(results[i]<res)
					res = results[i];
			}


			return res;
		}

		int findPlace(vector<int>ratings,int yourRating,int place){
			int turns = 0;
			vector<int> temp2;
			for(int i=0;i<ratings.size();i++){
				if(i==place)
					temp2.push_back(yourRating);
				temp2.push_back(ratings[i]);
			}

			int count = temp2.size();
			//cout << count << endl;
			vector<int> temp3 = temp2;;

			while(count!=1){
				vector<int> tmp;
				//for(int i=0;i<temp3.size();i++)
				//	cout << temp3[i] << " ";
				//cout << endl;
				for(int i=0;i<temp3.size();i=i+2){
					if(temp3[i]==yourRating||temp3[i+1]==yourRating){
						tmp.push_back(yourRating);
						if(temp3[i]>yourRating)
							turns++;
						if(temp3[i+1]>yourRating)
							turns++;
					}else
						tmp.push_back(max(temp3[i],temp3[i+1]));

				}

				temp3 = help(tmp);
				//for(int i=0;i<temp2.size();i++)
				//	cout << temp2[i] << " ";
				//cout << endl;

				count = count / 2;
			}

			return turns;
		}


			vector<int> help(vector<int>ratings){
				vector<int> tmp;
				for(int i=0;i<ratings.size();i++){
					tmp.push_back(ratings[i]);
				}

				return tmp;

		}



};
