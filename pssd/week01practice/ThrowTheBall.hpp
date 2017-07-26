/*
 * =====================================================================================
 *
 *       Filename:  ThrowTheBall.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/2017 10:00:19 PM
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

class ThrowTheBall{
	private:
		struct Node{
			int value;
			Node* next;
			Node* prev;
		};


	public:
		int timesThrown(int N,int M,int L){
			if(M==1){
				return 0;
			}else{
				int res;
				//set up 
				int initP;
				Node* player;
				Node* head = player;
				while(initP<N){
					Node* temp;
					player->next = temp;
					temp->prev = player;
					player = temp;
					initP++;
				}				
				player->next = head;
				head->prev = player;
				player = head;
				//start
				player->value += 1;
				res++;
				while(player->value != M){
					if(player->value%2 != 0){
						for(int i=0;i<L;i++){
							player = player->prev;
						}
					}else{
						for(int i=0;i<L;i++){
							player = player->next;
						}
					}
					player->value += 1;
					res++;
				}	

				return res;
			}
		}
};
