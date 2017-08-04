/*
 * =====================================================================================
 *
 *       Filename:  FibonacciDiv2.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/03/2017 09:58:44 PM
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



class FibonacciDiv2{
	bool check = true;


	public:
		int find(int N){
			int res = 0;
			if(N==0||N==1){
				return res;
			}
			int prev = 1;
			int next = 1;
			res = checkFib(1,1,N);

			return res;
		}

		int checkFib(int fib1,int fib2,int N){
			if(fib1+fib2==N){
				return 0;
			}else{
				if(fib2>N){
					if(abs(fib1-N)>=abs(fib2-N))
						return abs(fib2-N);
					else					
						return abs(fib1-N);
				}else{
					return checkFib(fib2,fib1+fib2,N);
				}
	
			}
			
		}


};
