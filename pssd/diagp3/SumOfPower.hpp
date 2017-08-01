#include <iostream>
#include <vector>


using namespace std;

class SumOfPower{


	public:
		int findSum(vector<int> array){
			int sum = 0;
			int subsum = 0;
			
			for(int i=0;i<array.size();i++){
				sum += array.size() * array[i];
			}


			return sum;
		}


};
