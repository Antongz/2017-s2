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
                        int id = 0;
                        int value = 0;
                        struct Node* next;
                        struct Node* prev;
                };


	public:
		int timesThrown(int N,int M,int L){
			if(M==1){
				return 0;
			}else{
                                int res = 0;
				//set up 
                                int initP = 0;
                                Node* player = new Node();
				Node* head = player;
                                while(initP<N-1){
                                        Node* temp = new Node();
                                        player->next = temp;
                                        player->id = initP;
                                        temp->prev = player;
                                        player = temp;
					initP++;
                                }
                                player->id = initP;
                                player->next = head;
                                head->prev = player;
                                player = head;

				//start
                                //cout << "start here" << endl;
                                player->value++;
                                bool check = true;
                                while(check){
                                       // cout << "passing" << endl;
                                        if(player->value==M){
                                            check = false;
                                            break;
                                        }
                                        //cout << player->value << endl;
                                        if(player->value%2 != 0){
                                                //cout << "pass to the prev" << endl;
						for(int i=0;i<L;i++){
							player = player->prev;
						}
					}else{
                                                //cout << "pass to the next" << endl;
						for(int i=0;i<L;i++){
							player = player->next;
						}
					}
                                        player->value++;
					res++;
				}	

				return res;
			}
		}
};

/*
int main(){
    ThrowTheBall test;
    cout << test.timesThrown(15,4,9) << endl;

    return 0;
}
*/
