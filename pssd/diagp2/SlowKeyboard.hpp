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
		diff--;
		const char sym[2] = ":";
		char* sec = new char[time.length()+1];
		strcpy(sec,time.c_str());
		char* min = strtok(sec,sym);
		sec = strtok(NULL,sym);
		
		
		int minute = atoi(min);
		int second = atoi(sec);
		int secondD = second/10;
		int secondR = second%10;
		int newMin = 1000000;

		int minD = minute/10;
		int minR = minute%10;
		if(secondD==5){
			if((secondD+1)>=6)
				secondD = 0;

			if(minD==5||minR==secondD){
				if(secondD==0){
					if((10-minR)>=minimum){
						if(diff*2< 10-minR){
							return minimum + diff*2;
						}else{
							return minimum + (10-minR) ;
						}
					}else{
						return minimum + 2;
					}
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
