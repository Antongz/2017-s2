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
                        //int length = sizeof(t)/sizeof(t[0]);
                        int i = 0;
                        int sum = 0;
                        Node* station = new Node();
			station->time = t[0];
                        sum += t[0];
			Node* head = station;
			i++;
                        while(i<length){
                                Node* temp = new Node();
				temp->time = t[i];
                                sum += t[i];
				temp->left = station;
				station->right = temp;
				station = temp;
				i++;
			}
			station->right = head;
			head->left = station;
			
                        //cout << "sum: " << sum << endl;

                        station = head;
                        /*  */
                        int leftT = 0;
                        int rightT = 0;
                        int mindiff = 0;	//store the minimum of difference
                        int res = 0;
                        for(int i=0;i<=length;i++){
                                station = head;
                                int start = 0;
                                while(start<i){
                                        station = station->right;
                                        start++;
                                }
                                for(int j=i+1;j<=length+2;j++){
                                	start = i;
                                    rightT = 0;
                                    leftT = 0;
                                    /*case1: from right */
									while(start<j){
                                    	rightT += station->time;
										station = station->right;
                                        start++;
                                    }
                                    //rightT += station->time;
                                    /*case2: from left */
                                    leftT = sum - rightT;

                                    if(i==0 && j==1){
										mindiff = abs(rightT-leftT);
                                        if(rightT>=leftT){
											res = leftT;
                                        }else{
											res = rightT;
										}
						
                                    }
                                    if(abs(rightT-leftT) < mindiff){
										mindiff = abs(rightT-leftT);
                                       	if(rightT>=leftT){
                                        	res = leftT;
                                        }else{
                                            res = rightT;
										}
									}				
                                     //cout << "leftT:"<<leftT<<"  rightT:"<<rightT<<endl;
							}
						}			
                        //cout << "mindiff " << mindiff << endl;

                        return res;
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
