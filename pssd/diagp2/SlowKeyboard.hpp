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
		
		int miniute = atoi(min);
		int second = atoi(sec);

		



	

		return minimum + diff*2;





		
	}


};
