#include <iostream>
#include <string.h>
#include <cstring>

using namespace std;

class SlowKeyboard{


public:
	int enterTime(string time){
		int res = 0;
		int diff = 0;
		int minimum = 4;
		char prev = time[0];
		for(int i=1;i<time.length();i++){
			if(prev!=time[i])
				diff++;

			prev = time[i];
		}

		const char sym[2] = ":";
		char* sec = new char[time.length()+1];
		strcpy(sec,time.c_str());
		char* min = strtok(sec,sym);
		sec = strtok(NULL,sym);
		
		
		int second = atoi(sec);
		int secondD = second/10;
		int secondR = second%10;
		int newMin = 1000000;

		int minD = min/10;
		int minR = min%10;
		if(secondD==5){
			if((secondD+1)>=6)
				secondD = 0;

			if(minD==5||minR==secondD){
				if(secondD==0){
					return minimum;
				}				
			}
		}		
		if(secondD<secondR){
			newMin = (10-secondR)+secondD;
		}


		if(newMin<diff*2){
			return newMin + minimum;
		}	

		return minimum + diff*2;





		
	}


};
