#include <iostream>
#include <string>

using namespace std;

class HenrysKey{

public:
	int howMany(string S){
		int res = 0;
		int length = s.length();	
		int i = 0;
		int diff = 0;
		bool checkSD = false;
		int same = 0;
		char* prev = S[0];
		for(i=1;i<length;i++){
			if(prev!=S[i]){
				diff++;
				checkSD = false;
			}
			if(prev==S[i]&&checkSD==false){
				checkSD = true;
				same++;
			}
			
		}

		if(length==1){
			return 1;
		}else{
			return = diff + 1;
		}
	}


};
