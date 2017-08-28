/*
 * =====================================================================================
 *
 *       Filename:  TicketBooker.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/22/2017 10:22:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>	//std::ifstream
#include <sstream> 
#include <string>
#include <queue>
#include <stdio.h>
#include <string.h>

/*input format: processID arrT priority age total_task*/

//using namespace std;

class TicketBooker{
	private:
        int threshold = 2;
        int worldTime = 0;

        struct Node{
            std::string id;
            int arrT;
            int priority;
            int age;
            int end;
            int waiting = 0;
            int tickets;
            int running = 0;
            int runs5 = 0;
            int interrupt = 0;
            Node* prev;
            Node* next;
        };
        Node* head_waitQue = nullptr;
        Node* tail_waitQue = nullptr;
        Node* headQue1 = nullptr;
        Node* tailQue1 = nullptr;
        Node* headQue2 = nullptr;
        Node* tailQue2 = nullptr;
        Node* headFinish = nullptr;
        Node* tailFinish = nullptr;
				

	public:
        TicketBooker(){

        }
        void setUp(std::string line){
			char *new1 = new char[line.length()+1];
			strcpy(new1,line.c_str());
			//char *li = strdup(new1);
			const char sp[2] = " ";
            Node* temp = new Node();
		 	temp->id = strtok(new1,sp);
			temp->arrT = std::stoi(strtok(NULL,sp));
			temp->priority = std::stoi(strtok(NULL,sp));
			temp->age = std::stoi(strtok(NULL,sp));
			temp->tickets = std::stoi(strtok(NULL,sp));
	  	
            //put it to wait queue
            if(temp->arrT>worldTime){
                if(head_waitQue==nullptr){
                    head_waitQue = temp, tail_waitQue = temp;
                }else{

                }
            }

            //for queue2
            if(temp->priority<=2){
                if(headQue2==nullptr)
                    headQue2 = temp, tailQue2 = temp;
                else{
                    tailQue2->next = temp;
                    temp->next = headQue2;
                    temp->prev = tailQue2;
                    headQue2->prev = temp;
                    tailQue2 = temp;
                }

            }else{
             //for queue1
                if(headQue1==nullptr){
                    headQue1 = temp;
                    tailQue1 = temp;
                }else{
                    tailQue1->next = temp;
                    temp->next = headQue1;
                    temp->prev = tailQue1;
                    headQue1->prev = temp;
                    tailQue1 = temp;
                    //std::cout << "testing" << std::endl;
                    //std::cout << temp->id << " " << temp->arrT << " " << temp->priority << " " << temp->age << " " << temp->tickets << std::endl;
                }
            }
		}

        void demoted_que1_to_que2(Node* node){
            if(node->priority<=2){
                Node* tempP = node; tempP = node->prev;
                Node* tempN = node; tempN = node->next;
                tempP->next = tempN;
                tempN->prev = tempP;

                //then move this node to the end of Queue2
                tailQue2->next = node;
                node->prev = tailQue2;
                node->next = headQue2;
                headQue2->prev = node;
                tailQue2 = node;
            }

        }

        //remove our node from queue and put it into our finish list
        void remove(Node* node){
            Node *tempP = node;
            Node *tempN = node;
            tempP = tempP->prev;
            tempN = tempN->next;
            tempP->next = tempN;
            tempN->prev = tempP;
            if(headFinish==nullptr){
                headFinish = node;
                tailFinish = node;
            }else{
                tailFinish->next = node;
            }

        }

        //for queue1: high priority first
        void HPF(){

        }
        //for queue1
        void RR(){
            Node* temp = headQue1;
            Node* temp1;
            while(temp!=nullptr){
                temp1 = temp->prev;
                if(temp1->runs5==5){
                    demoted_que1_to_que2(temp1);
                }

                if(temp->tickets<=5){
                    temp->running += temp->tickets;
                    worldTime += temp->tickets;
                    temp->tickets = 0;
                    remove(temp);
                }else{
                    temp->running += 5;
                    worldTime += 5;
                    temp->tickets -= 5;
                    temp->runs5++;
                }
                temp = temp->next;
            }
        }


        void FCFS(){

        }
        //aging is only for queue2
        void aging(Node* node){
            node->age--;
            node->priority--;
            if(node->priority<=2){
                Node* tempP = node; tempP = node->prev;
                Node* tempN = node; tempN = node->next;
                tempP->next = tempN;
                tempN->prev = tempP;

                //then move this node to the end of Queue2
                tailQue2->next = node;
                node->prev = tailQue2;
                node->next = headQue2;
                headQue2->prev = node;
                tailQue2 = node;
            }
        }
		void print(){
            std::cout << "print here" << std::endl;
            Node *temp = headFinish;
            while(temp!=nullptr){
                 std::cout << temp->id << " " << temp->arrT << " " << temp->priority << " " << temp->age << " " << temp->tickets << std::endl;
                temp = temp->next;
            }

        }
};




int main(int argc,char* argv[]){
	//std::cout << argc << " ";
	//std::cout << argv[1] << std::endl;
	int count = 0;
	//std::ifstream ifs(argv[1],std::ifstream::in);
	std::ifstream infile(argv[1]);
	std::string line;

	//testing
	TicketBooker test;
	//char c = ifs.get();
	while(std::getline(infile,line)){
        //std::cout << " "<< count << " ";
		std::istringstream iss(line);
        test.setUp(line);
		//c = ifs.get();
		std::cout << line << std::endl;
        //count++;
	}
    test.print();
	//ifs.close();

	return 0;
}
