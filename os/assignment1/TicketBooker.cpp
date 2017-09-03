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
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

/*input format: processID arrT priority age total_task*/

//using namespace std;

class TicketBooker{
	private:
        bool checkFirst = true;
        int threshold = 2;
        int worldTime = 0;
        std::vector<int> waitQueueT;
        int lengthQ1 = 0;
        int lengthQ2 = 0;
        int finallist = 0;
        int countAge = 0;
        int signID = 0;

        struct Node{
            bool demoq1q2 = false;
            bool serveq2 = false;
            bool checkStart = true;
            std::string id;
            int ID = 0;
            int arrT;
            int priority;
            int age = 0;
            int end;
            int ready = 0;
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

        /*all the functions for queue1*/
        //Depends on the priority
        void addQue1(Node* temp){
            lengthQ1++;
            if(headQue1==nullptr){             
                headQue1 = temp;    temp->next = temp; temp->prev = temp;
                tailQue1 = temp;
            }else{
                Node* tempH = headQue1;
                //if new node has the highest priority
                if(tempH->priority < temp->priority){
                    tailQue1->next = temp;
                    temp->next = tempH;
                    temp->prev = tailQue1;
                    tempH->prev = temp;
                    headQue1 = temp;
                }else{
                    //std::cout << temp->id << " " << lengthQ1 << std::endl;
                    int count = 0;
                    while(temp->priority<tempH->priority&&count<lengthQ1-1){
                        tempH = tempH->next;
                        count++;
                    }
                    while(temp->priority==tempH->priority&&count<lengthQ1-1){
                       // std::cout << temp->priority << " " << tempH->priority  << tempH->id << std::endl;
                        tempH = tempH->next;
                        count++;
                        if(temp->arrT<tempH->arrT)
                            break;
                        if(temp->arrT==tempH->arrT&&temp->ID<tempH->ID)
                            break;
                    }
                    //right now temp and tempH has at least the same priority
                    if(count==lengthQ1-1){
                        tailQue1 = temp;
                    }
                    //std::cout << std::endl;
                    tempH = tempH->prev;
                    Node* tempN = tempH->next;
                    tempN->prev = temp;
                    temp->next = tempN;
                    tempH->next = temp;
                    temp->prev = tempH;
                }
                //std::cout << "testing" << std::endl;
                //std::cout << temp->id << " " << temp->arrT << " " << temp->priority << " " << temp->age << " " << temp->tickets << std::endl;
            }         
        }

        void add_node_fromQ2_to_Q1(Node* temp){
            //std::cout << "add node from q2 to q1 " << lengthQ2 <<temp->id << std::endl;
            //checkAgingOccurTail = true;
            removeQue2(temp);
            insertQue1(temp);
        }


        void demoted_que1_to_que2(Node* node){
            if(node->priority<=2){
                //std::cout << "demote to q2 " << lengthQ1 <<std::endl;
                //node->demoteq1q2 = true;
                //std::cout << node->prev->id << std::endl;
                node->demoq1q2 = true;
                removeQue1(node);
                //then move this node to the end of Queue2
                addQue2(node);
            }else{
                removeQue1(node);
                insertQue1(node);
            }
        }

        //shift node by priority for queue1
        void insertQue1(Node* node){
            //adding node after currN
            Node* temp = headQue1;
            if(lengthQ1==0){
                lengthQ1++;
                headQue1 = node;
                tailQue1 = node;
                node->next = node;
                node->prev = node;
            }else if(lengthQ1==1&&node->priority==3){
                lengthQ1++;
                headQue1->next = node;
                headQue1->prev = node;
                node->next = headQue1;
                node->prev = headQue1;
                tailQue1 = node;
            }
            else{
                lengthQ1++;
                if(node->priority==3){
                    tailQue1->next = node;
                    node->prev = tailQue1;
                    headQue1->prev = node;
                    node->next = headQue1;
                    tailQue1 = node;
                }else{
                    if(node->priority>headQue1->priority){
                        headQue1->prev = node;
                        tailQue1->next = node;
                        node->prev = tailQue1;
                        node->next = headQue1;
                        headQue1 = node;
                    }else{
                        while(temp->priority>=node->priority&&temp->priority>3){
                            if(temp->next->priority<node->priority)
                                break;
                            temp = temp->next;
                        }
                        //wa want our previous
                        Node* tempN = temp->next;
                        node->next = tempN;
                        tempN->prev = node;
                        node->prev = temp;
                        temp->next = node;
                        if(temp==tailQue1){
                            tailQue1 = node;
                        }
                    }
                }
            }
        }

        void sortWaitQueT(){
            std::sort(waitQueueT.begin(),waitQueueT.end());
            std::reverse(waitQueueT.begin(),waitQueueT.end());
        }
        /*end here*/
        //remove our node from queue and put it into our finish list
        void remove(Node* node){
            Node *tempP = node;
            Node *tempN = node;
            tempP = tempP->prev;
            tempN = tempN->next;
            tempP->next = tempN;
            tempN->prev = tempP;
        }

        void removeQue2(Node* node){
            lengthQ2--;
            if(lengthQ2==0){
                headQue2 = nullptr;
                tailQue2 = nullptr;
            }else if(lengthQ2==1){
                Node* temp = node->next;
                headQue2 = temp;
                tailQue2 = temp;
                temp->next = temp;
                temp->prev = temp;
            }else{
                Node *tempP = node->prev;
                Node *tempN = node->next;
                tempP->next = tempN;
                tempN->prev = tempP;
                if(headQue2==node){
                    headQue2 = tempN;
                    tailQue2 = tempP;
                }
                if(tailQue2==node)
                    tailQue2 = tempP;
            }
            node->next = nullptr;
            node->prev = nullptr;
            if(node->tickets<=0){
                //std::cout << node->id << " " << std::endl;
                //node->prev = nullptr;
                //node->next = nullptr;
                addtoFinishList(node);
            }
        }

        void removeQue1(Node* node){
            lengthQ1--;
            if(lengthQ1==0){
                node->next = nullptr;
                node->prev = nullptr;
                headQue1 = nullptr;
                tailQue1 = nullptr;
            }else if(lengthQ1==1){
                //std::cout<<"hello"<<std::endl;
                Node* temp = node->next;
                headQue1 = temp;
                headQue1->next = temp;
                headQue1->prev = temp;
                tailQue1 = temp;
            }else{
               // std::cout << "remove node: " << node->id << " " << node->next->id << std::endl;
                Node *tempP = node->prev;
                Node *tempN = node->next;
                if(headQue1==node){
                    headQue1 = tempN;   tailQue1 = tempP;
                }
                if(tailQue1==node){
                    tailQue1 = tempP;   headQue1 = tempN;
                }
                tempP->next = tempN;
                tempN->prev = tempP;
                //std:: cout << headQue1->priority <<"head is" << headQue1->id << " " << headQue1->prev->id << " " << lengthQ1 << std:: endl;
            }

            //node->prev = nullptr;
            //node->next = nullptr;

            if(node->tickets<=0){
                //std::cout << node->id << " " << std::endl;
                //node->prev = nullptr;
                //node->next = nullptr;
                addtoFinishList(node);
            }
        }

        int checkNewArrive(){
            int checkT = 0;
            int count = 0;
            //testing for queue2
            int runtime = std::min(headQue2->tickets,20);

            for(int i=(short)waitQueueT.size()-1;i>=0;i--){
                //std::cout << "find waitNode" << waitQueueT[i] << std::endl;
                if(waitQueueT[i]<=worldTime+runtime){
                    count++;
                    checkT = std::min(worldTime+runtime,waitQueueT[i]);
                }
            }
            if(checkT>0){
                Node* tempW = head_waitQue;
                while(tempW->arrT!=checkT){
                    std::cout << tempW->arrT << std::endl;
                    tempW = tempW->next;
                }
                if(tempW->priority<=2)
                    return 0;
            }
            return checkT;
        }



        void removeWaitQue(Node* node){
            if(waitQueueT.size()==1){
                head_waitQue = nullptr;
                tail_waitQue = nullptr;
            }else{
                Node* tempP = node->prev;
                Node* tempN = node->next;
                if(node==head_waitQue){
                    head_waitQue = tempN;
                    tail_waitQue = tempP;
                }
                tempP->next = tempN;
                tempN->prev = tempP;
                node->prev = nullptr;
                node->next = nullptr;
            }
        }

        /*all the functions for queue2*/

        void addQue2(Node* temp){
            if(headQue2==nullptr){
                lengthQ2++;
                headQue2 = temp;
                tailQue2 = temp;
                temp->next = temp;
                temp->prev = temp;
            }else{
                lengthQ2++;
                tailQue2->next = temp;
                temp->next = headQue2;
                temp->prev = tailQue2;
                headQue2->prev = temp;
                tailQue2 = temp;
            }
        }


        //aging is only for queue2
        void aging(Node* node){
            if(node->demoq1q2){
                node->age = 0;
                node->demoq1q2 = false;
            }else if(node->serveq2){
                node->age = 0;
                node->serveq2 = false;
            }else{
                node->age = node->age + 1;
            }
            if(node->age==8){
                node->priority++;
                node->age = 0;
            }
            if(node->priority>2){
                //then move this node to Queue1
                add_node_fromQ2_to_Q1(node);
            }
        }

        /*end here*/

        /*for printing our result*/
        void addtoFinishList(Node* node){
            finallist++;
            //node->prev = nullptr;
            //node->next = nullptr;
            if(headFinish==nullptr){
                headFinish = node;
                tailFinish = node;
            }else{
                tailFinish->next = node;
                tailFinish = node;
            }
        }


	public:
        TicketBooker(){}
        void setUp(std::string line){
			char *new1 = new char[line.length()+1];
			strcpy(new1,line.c_str());
			//char *li = strdup(new1);
			const char sp[2] = " ";
            Node* temp = new Node();
            /*input format: processID arrT priority age total_task*/
		 	temp->id = strtok(new1,sp);
			temp->arrT = std::stoi(strtok(NULL,sp));
			temp->priority = std::stoi(strtok(NULL,sp));
			temp->age = std::stoi(strtok(NULL,sp));
            temp->age = 0;
			temp->tickets = std::stoi(strtok(NULL,sp));
            //temp->running = temp->tickets;

            //std::cout << "testing" << std::endl;
            //std::cout << temp->id << " " << temp->arrT << " " << temp->priority << " " << temp->age << " " << temp->tickets << std::endl;

            //put it to wait queue
            if(temp->arrT>worldTime){
                if(temp->priority<=2)
                    temp->demoq1q2 = true;
                if(head_waitQue==nullptr){
                    head_waitQue = temp; tail_waitQue = temp;
                    temp->next = temp; temp->prev = temp;
                    waitQueueT.push_back(temp->arrT);
                }else{
                    tail_waitQue->next = temp;
                    temp->next = head_waitQue;
                    head_waitQue->prev = temp;
                    temp->prev = tail_waitQue;
                    tail_waitQue = temp;
                    waitQueueT.push_back(temp->arrT);
                }
            }else{
                //for queue2
                if(temp->priority<=2){
                    temp->ID = signID;
                    signID++;
                    addQue2(temp);
                }else{
                 //for queue1
                    temp->ID = signID;
                    signID++;
                    addQue1(temp);
                    //std::cout << "hereQue1" << std:: endl;
                }
            }
            sortWaitQueT();
		}


        void serving(){
            while(lengthQ1>0||lengthQ2>0){
                servingQ1();
                servingQ2();
            }
        }


        //for serving queue1
        void servingQ1(){         
            Node* temp = headQue1;
            int count = 0;
            while(lengthQ1>0){
                temp = headQue1;
                //serving our queue1
                if(temp->tickets<=5){
                    //std::cout << temp->id << " finish " << worldTime+temp->tickets<<std::endl;
                    if(temp->checkStart){
                        temp->ready = worldTime;
                        temp->checkStart = false;
                    }
                    temp->running += temp->tickets;
                    worldTime += temp->tickets;
                    temp->end = worldTime;
                    temp->tickets = 0;              
                    //removeQue1(temp);
                    //std::cout << headQue1->id << " " << tailQue1->id << " " << temp->id  << temp->next->id << std::endl;
                    if(lengthQ1==0){
                        temp = nullptr;
                        break;
                    }
                }else{          
                    //std::cout << temp->id << " " << temp->tickets << " " << worldTime <<std::endl;
                    if(temp->checkStart){
                        temp->ready = worldTime;
                        temp->checkStart = false;
                    }
                    temp->running += 5;
                    worldTime += 5;
                    temp->tickets -= 5;
                    temp->runs5++;
                }

                //adding new arrive process to the list
                count = 0;
                for(int i=(short)waitQueueT.size()-1;i>=0;i--){
                    //std::cout << "find waitNode" << waitQueueT[i] << std::endl;
                    if(waitQueueT[i]<=worldTime){
                        count++; 
                        Node* tempW = head_waitQue;
                        while(tempW->arrT!=waitQueueT[i]){
                            //std::cout << tempW->arrT << std::endl;
                            tempW = tempW->next;
                        }
                        //if it's queue1 / queue2
                        if(tempW->priority>2){
                            //std::cout << "insert new node to que1 " << lengthQ1 << std::endl;
                            removeWaitQue(tempW);
                            insertQue1(tempW);
                        }else{
                            removeWaitQue(tempW);
                            addQue2(tempW);
                        }
                    }
                }
                if(count>0){
                    for(int i=0; i<count;i++)
                        waitQueueT.pop_back();
                }


                if(temp->tickets==0)
                    removeQue1(temp);
                else{
                    if(temp->runs5==5){
                        temp->priority--;
                        //std::cout << "demote" << " " << temp1->id <<std::endl;
                        demoted_que1_to_que2(temp);
                        temp->runs5 = 0;
                        if(lengthQ1<=0){
                            temp = nullptr;
                            break;
                        }
                    }else{
                        removeQue1(temp);
                        insertQue1(temp);
                    }
                }


                //aging process for queue2
                int itr2 = 0;
                Node* temp2 = headQue2;
                Node* prev;
                //std::cout << "aging  " << lengthQ2 << std::endl;
                int lengthq2 = lengthQ2;
                if(lengthq2>0){
                    while(itr2<lengthq2){
                        //std::cout << lengthQ2 << std::endl;
                        prev = temp2;
                        temp2 = temp2->next;
                        aging(prev);
                        //std::cout << prev->id << " " << prev->age << " " << prev->priority << std::endl;
                        itr2++;
                    }
                }    
            }
        }




        void servingQ2(){
            //std::cout << lengthQ1 << std::endl;
            int count = 0;
            int checkT = 0;
            Node* temp = headQue2;
            while(lengthQ1==0&&lengthQ2>0){
                checkT = 0;
                temp = headQue2;

                //adding new arrive process to the list
                count = 0;
                checkT = checkNewArrive();

                //there will arrive a new process
                if(checkT>0){
                    temp->serveq2 = true;
                    temp->running += (checkT-worldTime);
                    temp->tickets -= (checkT-worldTime);
                    worldTime += (checkT-worldTime);
                    temp->age = 0;

                }else{
                    if(temp->tickets<=20){
                        //std::cout << temp->id << " finish " << worldTime+temp->tickets<<std::endl;
                        if(temp->checkStart){
                            temp->ready = worldTime;
                            temp->checkStart = false;
                        }
                        temp->running += temp->tickets;
                        worldTime += temp->tickets;
                        temp->end = worldTime;
                        temp->tickets = 0;
                    }else{
                        //std::cout << temp->id << " " << temp->tickets << " " << worldTime <<std::endl;
                        if(temp->checkStart){
                            temp->ready = worldTime;
                            temp->checkStart = false;
                        }
                        temp->serveq2 = true;
                        temp->running += 20;
                        worldTime += 20;
                        temp->tickets -= 20;
                        temp->age = 0;
                    }

                }

                //adding new process from waitqueue
                if(checkT>0){
                    Node* tempW = head_waitQue;
                    count++;
                    while(tempW->arrT!=checkT){
                        //std::cout << tempW->arrT << std::endl;
                        tempW = tempW->next;
                    }
                    //if it's queue1 / queue2
                    if(tempW->priority>2){
                        //std::cout << "insert new node to que1 " << lengthQ1 << std::endl;
                        removeWaitQue(tempW);
                        insertQue1(tempW);
                    }else{
                        removeWaitQue(tempW);
                        addQue2(tempW);
                    }
                }
                if(count>0){
                    for(int i=0; i<count;i++)
                        waitQueueT.pop_back();
                }




                //aging process for queue2
                int itr2 = 0;
                Node* temp2 = headQue2;
                Node* prev;
                //std::cout << "aging  " << lengthQ2 << std::endl;
                int lengthq2 = lengthQ2;
                if(lengthq2>0){
                    while(itr2<lengthq2){
                        //std::cout << lengthQ2 << std::endl;
                        prev = temp2;
                        temp2 = temp2->next;
                        aging(prev);
                        //std::cout << prev->id << " " << prev->age << " " << prev->priority << std::endl;
                        itr2++;
                    }
                }

                removeQue2(temp);
                if(temp->tickets>0)
                    addQue2(temp);
            }
        }

        void print(){
            std::cout << "print here" << std::endl;
            std::cout << "queue1: length: " << lengthQ1 << std::endl;
            Node *temp = headQue1;
            std::cout << temp->id << " " << temp->arrT << " " << temp->priority << " " << temp->age << " " << temp->tickets << std::endl;
            temp = temp->next;
            while(temp!=headQue1){
                std::cout << temp->id << " " << temp->arrT << " " << temp->priority << " " << temp->age << " " << temp->tickets << std::endl;
                temp = temp->next;
            }

            std::cout << "queue2 " << lengthQ2 << std::endl;
            Node *temp2 = headQue2;
            std::cout << temp2->id << " " << temp2->arrT << " " << temp2->priority << " " << temp2->age << " " << temp2->tickets << std::endl;
            temp2 = temp2->next;
            while(temp2!=headQue2){
                std::cout << temp2->id << " " << temp2->arrT << " " << temp2->priority << " " << temp2->age << " " << temp2->tickets << std::endl;
                temp2 = temp2->next;
            }
/*
            std::cout << "waitqueue" << std::endl;
            Node *temp3 = head_waitQue;
            std::cout << temp3->id << " " << temp3->arrT << " " << temp3->priority << " " << temp2->age << " " << temp3->tickets << std::endl;
            temp3 = temp3->next;
            while(temp3!=head_waitQue){
                std::cout << temp3->id << " " << temp3->arrT << " " << temp3->priority << " " << temp2->age << " " << temp3->tickets << std::endl;
                temp3 = temp3->next;
            }
            */
            //std::cout << "waitqueue" << std::endl;
            //waitQueueT.pop_back();
            //for(int i=0;i<waitQueueT.size();i++){
            //    std::cout << waitQueueT[i] << std::endl;
            //}
        }

        void printQue2(){
            std::cout << "queue2 " << lengthQ2 << std::endl;
            Node *temp2 = headQue2;
            std::cout << temp2->id << " " << temp2->arrT << " " << temp2->priority << " " << temp2->age << " " << temp2->tickets << " " << temp2->age << std::endl;
            temp2 = temp2->next;
            while(temp2!=headQue2){
                std::cout << temp2->id << " " << temp2->arrT << " " << temp2->priority << " " << temp2->age << " " << temp2->tickets << std::endl;
                temp2 = temp2->next;
            }
        }
        void printQue1(){
            std::cout << "queue1: length: " << lengthQ1 << std::endl;
            Node *temp = headQue1;
            std::cout << temp->id << " " << temp->arrT << " " << temp->priority << " " << temp->age << " " << temp->tickets << " " << temp->runs5 << std::endl;
            temp = temp->next;
            while(temp!=headQue1){
                std::cout << temp->id << " " << temp->arrT << " " << temp->priority << " " << temp->age << " " << temp->tickets << std::endl;
                temp = temp->next;
            }
        }

        void printF(){
            Node *tempf = headFinish;
            int count = 0;
            std::cout << "name  arrival     end     ready   running     waiting" << std::endl;

            while(tempf!=nullptr&&count<finallist){
                tempf->waiting = tempf->end - tempf->running - tempf->ready;
                 std::cout << tempf->id << " " << tempf->arrT << " " << tempf->end << " " <<
                              tempf->ready << " " << tempf->running << " " << tempf->waiting << std::endl;
                 tempf = tempf->next;
                 count++;
            }
        }
};




int main(int argc,char* argv[]){
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
        //std::cout << line << std::endl;
        //count++;
	}
    //test.print();
	//ifs.close();
    test.serving();
    //test.servingQ1();
    //test.servingQ2();
    //test.printQue1();
    //test.servingQ1();
    //test.servingQ2();
    //test.printQue2();
    //std::cout << std::endl;
    //test.printQue1();
    test.printF();

	return 0;
}
