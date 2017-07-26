/*
 * =====================================================================================
 *
 *       Filename:  EggCartons.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/25/2017 04:09:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

class EggCartons{
	
	public:
		int minCartons(int n){
                        int res = 0;
			bool check = true;
			while(check){
				if(n<0){
					check = false;
					res = -1;
				}else if(n%8==0){
					res += n/8;
					check = false;
				}else{
					n -= 6;
					res++;				
				}	
			}
			return res;
		}

};
/*
int main(){
    EggCartons test;
    cout << test.minCartons(4) << endl;

}
*/
