#include <iostream>
#include <vector>
#include <string>
#include <string.h>


using namespace std;


class GoingUp{

	public:
		int minRemove(int a,int b,int c){
			int res = 0;
			if(a<b&&b<c)
				return 0;
			if(b<=1||c<=2)
				return -1;

			else{
				if(b<=a)
					return a-b+1+minRemove(a-(a-b+1),b,c);
				if(c<=b)
					return b-c+1+minRemove(a,b-(b-c+1),c);
				if(c<=a)
					return a-c+1+minRemove(a-(a-c+1)-1,b,c); 
			}
		}
		

};


int main(){
	GoingUp test;
	int a,b,c;
	cin>>a;
	cin>>b;
	cin>>c;
	cout << test.minRemove(a,b,c) << endl;

}
