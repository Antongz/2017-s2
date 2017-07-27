/*
 * =====================================================================================
 *
 *       Filename:  PartySeats.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/27/2017 11:29:41 AM
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
#include <string.h>
#include <stdio.h>
#include <cstring>
//use strtok();

using namespace std;

class PartySeats{
	struct Node{
		string name;
		string gender;
		Node* next;
	};

	public:
        vector<string> seating(vector<string> attendees){
            /*basic setup and assign the initial value*/
            vector<string> res;
			const char space[2] = " ";
			Node* host = new Node();
			host->name = "HOST";
			Node* hostess = new Node();
			hostess->name = "HOSTESS";

            /* set up */
            int number = attendees.size();
			int doubleCheck = number/2;
            if(number%4!=0 || number<4){
                return res;
            }
            int boyN = 0;
            int girlN = 0;
            /*sorting our list first*/
            for(int i=0;i<number;i++){
                for(int j=0;j<number;j++){
                    if(attendees[i][0]<attendees[j][0]){
                        string temp = attendees[j];
                        attendees[j] = attendees[i];
                        attendees[i] = temp;
                    }
					if(attendees[i][0]==attendees[j][0]){
						bool check = true;
						int k = 1;
						while(check){
							if(attendees[i][k]<attendees[j][k]){
 								string temp = attendees[j];
 	                       		attendees[j] = attendees[i];
    	                    	attendees[i] = temp;
								check = false;
							}
							if(attendees[i][k]>attendees[j][k]){
								check = false;
							}
							k++;
						}
					}
                }
            }

            int i = 1;
            Node *temp = new Node();
            Node* girls_head;
            Node* boys_head;
            Node* girls;
            Node* boys;
            char *gend = new char[attendees[0].length()+1];
            strcpy(gend,attendees[0].c_str());
            char* name = strtok(gend,space);
            gend = strtok(NULL,space);
            temp->name = name;
            temp->gender = gend;
            if(temp->gender=="boy"){
                boyN++;
                boys = temp;
                boys_head = boys;
            }else{
                girlN++;
                girls = temp;
                girls_head = girls;
            }
			while(i<number){
                Node *temp = new Node();
                char *gend = new char[attendees[i].length()+1];
                strcpy(gend,attendees[i].c_str());
                char* name = strtok(gend,space);
                gend = strtok(NULL,space);
                temp->name = name;
                temp->gender = gend;
                if(temp->gender=="boy"){
                    if(boyN==0){
                        boys = temp; boys_head = boys;
                    }else{
                        boys->next = temp;
                        boys = temp;
                    }
                    boyN++;
                }else{
                    if(girlN==0){
                        girls = temp; girls_head = girls;
                    }else{
                        girls->next = temp;
                        girls = temp;
                    }
                    girlN++;
                }
				i++;
			}

            boys = boys_head;
            girls = girls_head;
            /* test */
            //cout << boyN << girlN << endl;
            if(boyN!=girlN){
                return res;
            }

            //return this list
            int girlL = 0;
            int boyL = 0;
            int count = 0;
            Node* tempR = host;
            boyL++;
            res.push_back(tempR->name);
            while(count<number){
                if(count==(number/2)){
                    tempR->next = hostess;
                    tempR = hostess;
                    res.push_back(tempR->name);
                    girlL++;
                }
                /*add girl*/
                if(boyL>girlL){
                    tempR->next = girls;
                    tempR = girls;
                    girls = girls->next;
                    res.push_back(tempR->name);
                    girlL++;
                }else{
                /*add boy*/
                    tempR->next = boys;
                    tempR = boys;
                    boys = boys->next;
                    res.push_back(tempR->name);
                    boyL++;
                }
                count++;
            }



			return res;
		}
};

/*
int main(){

	PartySeats test;
    vector<string> att = {"BOB boy","SUZIE girl","DAVE boy","JO girl",
                          "AL boy","BOB boy","CARLA girl","DEBBIE girl"};

    vector<string> res = test.seating(att);
    for(int i=0;i<res.size();i++){
        cout << res[i] << endl;
    }

	return 0;
}
*/
