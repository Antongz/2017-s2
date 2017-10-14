/*
 * =====================================================================================
 *
 *       Filename:  CubeStickers.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/13/17 02:10:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class CubeStickers{

public:
	string isPossible(vector<string> sticker){
		vector<string> colors;
		vector<int> colorsN;

		for(int i=0;i<(int)sticker.size();i++){
			string temp = sticker[i];
			bool check = true;
			for(int j=0;j<(int)colors.size();j++){
				if(temp==colors[j]){
					colorsN[j]++;
					check = false;
					break;
				}
			}
			if(check){
				colors.push_back(temp);
				colorsN.push_back(1);
			}
		}

		int count = 0;
		for(int i=0;i<(int)colorsN.size();i++){
			if(colorsN[i]>=2)
				count++;
		}

        if(count>=3||(count==1&&colorsN.size()>=5)||(count==2&&colorsN.size()>=4))
			return "YES";
		else
			return "NO";
	}

};
