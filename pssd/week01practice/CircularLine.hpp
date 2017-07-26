/*
 * =====================================================================================
 *
 *       Filename:  CircularLine.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/25/2017 12:56:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */


#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class CircularLine{
	struct Node{
                int time = 0;
		Node* left;
		Node* right;
	};

	public:
		int longestTravel(vector<int> t){
			/* do the basic setup */
                        int length = t.size();
                        //cout << length << endl;
                        //int length = sizeof(t)/sizeof(t[0]);
                        int i = 0;
                        Node* station = new Node();
			station->time = t[0];
			Node* head = station;
			i++;
                        while(i<length-1){
                                Node* temp = new Node();
				temp->time = t[i];
				temp->left = station;
				station->right = temp;
				station = temp;
				i++;
			}
			station->right = head;
			head->left = station;
			
			/*  */
			int leftT,rightT;
                        int mindiff;	//store the minimum of difference
			int res;
			for(int i=0;i<length;i++){
				rightT = 0;
				leftT = 0;
                                station = head;
                                int start = 0;
                                while(start<i){
                                        station = station->right;
                                        start++;
                                }
                                for(int j=i+1;j<length;j++){
                                        //int target = j - i;
					/* from right */
                                        Node* temp = station;
					while(start<j){
						rightT += station->time;
						station = station->right;
                                                start++;
					}				
					/* from left */
					while(temp!=station){
						leftT += temp->time;
						temp = temp->left;
					}
					
                                        if(i==0 && j==1){
						mindiff = abs(rightT-leftT);
                                                if(rightT>=leftT){
							res = leftT;
                                                }else{
							res = rightT;
						}
						
					}else if(abs(rightT-leftT)<mindiff){
						mindiff = abs(rightT-leftT);
                                                if(rightT>=leftT){
							res = rightT;
                                                }else{
							res = leftT;
						}
					}
				}
			}			

                        return res+1;
		}

};
/*
int main(){
    CircularLine test;
    vector<int> input = {1,1,1,1,4};
    cout << test.longestTravel(input) << endl;

    return 0;
}
*/
