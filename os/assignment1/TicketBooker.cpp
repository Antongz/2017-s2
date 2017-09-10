/*
 * =====================================================================================
 *		   Course:	Operating Systems
 *       Filename:  TicketBooker.cpp
 *    Description:  Assignment 1
 *
 *        Version:  1.1
 *        Created:  08/22/2017 10:22:48 PM
 *       Revision:  none
 *       Compiler:  gcc -std=c++11
 *
 *			Author:	Yi-Ting, Hsieh	(a1691807), a1691807@student.adelaide.edu.au
 *					Gray, Simon		(a1687852),	a1687852@student.adelaide.edu.au
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
//	Max tickets queue 1 can do at a time
#define Q1MAX 5
//	Max tickets queue 2 can do at a time, uninterupted
#define Q2MAX 20
//	Age to	increase priority
#define AGELIMIT 8

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

        //	What comprises the Node object
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

        Node* headWaitQueue	= nullptr;
        Node* tailWaitQueue	= nullptr;
        Node* headQue1		= nullptr;
        Node* tailQue1		= nullptr;
        Node* headQue2		= nullptr;
        Node* tailQue2		= nullptr;
        Node* headFinish	= nullptr;
        Node* tailFinish	= nullptr;

//	Adds node to queue 1 depending on priority
        void addQue1(Node* temp){
            lengthQ1++;
            // Empty queue situation
            if(headQue1==nullptr){
                headQue1 = temp;
                temp->next = temp;
                temp->prev = temp;
                tailQue1 = temp;
            }
            else{
                Node* tempH = headQue1;
                //	If new node has the highest priority
                if(tempH->priority < temp->priority){
                    tailQue1->next = temp;
                    temp->next = tempH;
                    temp->prev = tailQue1;
                    tempH->prev = temp;
                    headQue1 = temp;
                }
                else{
                    int count = 0;
                    while(temp->priority<tempH->priority&&count<lengthQ1-1){
                        tempH = tempH->next;
                        count++;
                    }
                    while(temp->priority==tempH->priority&&count<lengthQ1-1){
                        tempH = tempH->next;
                        count++;
                        if(temp->arrT<tempH->arrT)
                            break;
                        if(temp->arrT==tempH->arrT&&temp->ID<tempH->ID)
                            break;
                    }
                    //	Right now temp and tempH has at least the same priority
                    if(count==lengthQ1-1)
                        tailQue1 = temp;
                    tempH = tempH->prev;
                    Node* tempN = tempH->next;
                    tempN->prev = temp;
                    temp->next = tempN;
                    tempH->next = temp;
                    temp->prev = tempH;
                }
            }
        }

//	Move queue 2 to queue 1
        void moveQ2toQ1(Node* temp){
            removeQue2(temp);
            insertQue1(temp);
        }

//	Move node, if priority low enough queue 2, else queue 1
        void demoteQ1(Node* node){
            //	Priority not good enough for queue 1
            if(node->priority<=2){
                node->demoq1q2 = true;
                removeQue1(node);
                addQue2(node);
            }
            //	Priority high enough for queue 1
            else{
                removeQue1(node);
                insertQue1(node);
            }
        }

//	Shift node by priority for queue1
        void insertQue1(Node* node){
            Node* temp = headQue1;
            // No nodes currently in queue
            if(lengthQ1==0){
                lengthQ1++;
                headQue1 = node;
                tailQue1 = node;
                node->next = node;
                node->prev = node;
            }
            //	Puts at end of node chain
            else if(lengthQ1==1&&node->priority==3){
                lengthQ1++;
                headQue1->next = node;
                headQue1->prev = node;
                node->next = headQue1;
                node->prev = headQue1;
                tailQue1 = node;
            }
            else{
                lengthQ1++;
                //	Add to end of node chain
                if(node->priority==3){
                    tailQue1->next = node;
                    node->prev = tailQue1;
                    headQue1->prev = node;
                    node->next = headQue1;
                    tailQue1 = node;
                }
                else{
                    // Add to head of node chain with higher priority then head
                    if(node->priority>headQue1->priority){
                        headQue1->prev = node;
                        tailQue1->next = node;
                        node->prev = tailQue1;
                        node->next = headQue1;
                        headQue1 = node;
                    }
                    //	Finds place to add node in chain
                    else{
                        //	Finds location to add node
                        while(temp->priority>=node->priority&&temp->priority>3){
                            //	Once it finds it spots breaks from while
                            if(temp->next->priority<node->priority)
                                break;
                            temp = temp->next;
                        }
                        Node* tempN = temp->next;
                        node->next = tempN;
                        tempN->prev = node;
                        node->prev = temp;
                        temp->next = node;
                        //	Adjust node tail if needed
                        if(temp==tailQue1){
                            tailQue1 = node;
                        }
                    }
                }
            }
        }

//	Sorting the waiting queue
        void sortWaitQueT(){
            std::sort(waitQueueT.begin(),waitQueueT.end());
            std::reverse(waitQueueT.begin(),waitQueueT.end());
        }

//	Remove node from queue 2
        void removeQue2(Node* node){
            lengthQ2--;
            //	Removing last node of chain
            if(lengthQ2==0){
                headQue2 = nullptr;
                tailQue2 = nullptr;
            }
            //	Only one node left in chain
            else if(lengthQ2==1){
                Node* temp = node->next;
                headQue2 = temp;
                tailQue2 = temp;
                temp->next = temp;
                temp->prev = temp;
            }
            //	More than one node, patches around it
            else{
                Node *tempP = node->prev;
                Node *tempN = node->next;
                tempP->next = tempN;
                tempN->prev = tempP;
                //	Modify head and tail pointers if needed
                if(headQue2==node){
                    headQue2 = tempN;
                    tailQue2 = tempP;
                }
            }
            node->next = nullptr;
            node->prev = nullptr;
            if(node->tickets<=0){
                addtoFinishList(node);
            }
        }
    //	Remove node from queue 1
        void removeQue1(Node* node){
            lengthQ1--;
            //	Removing last node of chain
            if(lengthQ1==0){
                headQue1 = nullptr;
                tailQue1 = nullptr;
            }
            //	Only one node left in chain
            else if(lengthQ1==1){
                Node* temp = node->next;
                headQue1 = temp;
                headQue1->next = temp;
                headQue1->prev = temp;
                tailQue1 = temp;
            }
            else{
                Node *tempP = node->prev;
                Node *tempN = node->next;
                //	Fix up head node if needed
                if(headQue1==node){
                    headQue1 = tempN;
                    tailQue1 = tempP;
                }
                //	Fix up tail node if needed
                if(tailQue1==node){
                    tailQue1 = tempP;
                    headQue1 = tempN;
                }
                tempP->next = tempN;
                tempN->prev = tempP;
            }
            //	Case where process has finished
            if(node->tickets<=0){
                addtoFinishList(node);
            }
        }

//	Checks if any nodes are ready to be added from waiting list
        int checkNewArrive(){
            int checkT = 0;
            //	Check if any nodes are ready to get added
            int runtime = std::min(headQue2->tickets,Q2MAX);

            for(int i=(short)waitQueueT.size()-1;i>=0;i--){
                if(waitQueueT[i]<=worldTime+runtime){
                    checkT = std::min(worldTime+runtime,waitQueueT[i]);
                }
            }
            if(checkT>0){
                Node* tempW = headWaitQueue;
                while(tempW->arrT!=checkT){
                    std::cout << tempW->arrT << std::endl;
                    tempW = tempW->next;
                }
                if(tempW->priority<=2){
                    return 0;
                }
            }
            return checkT;
        }

//	Remove from queue
        void removeWaitQue(Node* node){
            //	Last node in wait queue
            if(waitQueueT.size()==1){
                headWaitQueue = nullptr;
                tailWaitQueue = nullptr;
            }
            //	Patch nodes around moved node
            else{
                Node* tempP = node->prev;
                Node* tempN = node->next;
                if(node==headWaitQueue){
                    headWaitQueue = tempN;
                    tailWaitQueue = tempP;
                }
                tempP->next = tempN;
                tempN->prev = tempP;
                node->prev = nullptr;
                node->next = nullptr;
            }
        }

//	Adds node to queueu 2
        void addQue2(Node* temp){
            //	Adds to queue 2 if its empty
            if(headQue2==nullptr){
                lengthQ2++;
                headQue2 = temp;
                tailQue2 = temp;
                temp->next = temp;
                temp->prev = temp;
            }
            else{	//	Adds to end of queue
                lengthQ2++;
                tailQue2->next = temp;
                temp->next = headQue2;
                temp->prev = tailQue2;
                headQue2->prev = temp;
                tailQue2 = temp;
            }
        }

//	Age all nodes in queue 2 to limit starvation
        void aging(Node* node){
            if(node->demoq1q2){
                node->age = 0;
                node->demoq1q2 = false;
            }
            else if(node->serveq2){
                node->age = 0;
                node->serveq2 = false;
            }
            else{
                node->age = node->age + 1;
            }
            //	Increases priority if age is above limit
            if(node->age==AGELIMIT){
                node->priority++;
                node->age = 0;
            }
            //	Check if its priority if high enough to move queue
            if(node->priority>2){
                moveQ2toQ1(node);
            }
        }

//	Move node to finished list
        void addtoFinishList(Node* node){
            finallist++;
            //	First node to finish
            if(headFinish==nullptr){
                headFinish = node;
                tailFinish = node;
            }
            //	Adds node to end of finished list
            else{
                tailFinish->next = node;
                tailFinish = node;
            }
        }

    public:
        TicketBooker(){}
//	Parsing input and setting up initial queue states
        void setUp(std::string line){
            char *new1 = new char[line.length()+1];
            strcpy(new1,line.c_str());
            const char sp[2] = " ";
            Node* temp = new Node();
            //	File input format: processID arrT priority age tickets
            temp->id		= strtok(new1,sp);
            temp->arrT		= std::stoi(strtok(NULL,sp));
            temp->priority	= std::stoi(strtok(NULL,sp));
            temp->age		= std::stoi(strtok(NULL,sp));
            temp->age		= 0;
            temp->tickets	= std::stoi(strtok(NULL,sp));

            //	Put it to wait queue
            if(temp->arrT>worldTime){
                if(temp->priority<=2){
                    temp->demoq1q2 = true;
                }
                if(headWaitQueue==nullptr){
                    headWaitQueue = temp;
                    tailWaitQueue = temp;
                    temp->next = temp;
                    temp->prev = temp;
                    waitQueueT.push_back(temp->arrT);
                }
                else{
                    tailWaitQueue->next = temp;
                    temp->next = headWaitQueue;
                    headWaitQueue->prev = temp;
                    temp->prev = tailWaitQueue;
                    tailWaitQueue = temp;
                    waitQueueT.push_back(temp->arrT);
                }
            }
            else{
                //	Put in queue 2
                if(temp->priority<=2){
                    temp->ID = signID;
                    signID++;
                    addQue2(temp);
                }
                //	Put in queue 1
                else{
                    temp->ID = signID;
                    signID++;
                    addQue1(temp);
                }
            }
            //	Sort all nodes in waiting queue
            sortWaitQueT();
        }

//	Decides what queue to serve
        void serving(){
            //	Always serve queue 1, then queue 2, continue till both empty
            while(lengthQ1>0||lengthQ2>0){
                servingQ1();
                servingQ2();
            }
        }

//	Serving queue 1
        void servingQ1(){
            Node* temp = headQue1;
            //	Need to empty queue 1 before moving on
            while(lengthQ1>0){
                temp = headQue1;
                // Checks if amount of tickets node has left is less that amount it deals with
                if(temp->tickets<=Q1MAX){
                    if(temp->checkStart){
                        temp->ready = worldTime;
                        temp->checkStart = false;
                    }
                    temp->running += temp->tickets;
                    worldTime += temp->tickets;
                    temp->end = worldTime;
                    temp->tickets = 0;
                    if(lengthQ1==0){
                        temp = nullptr;
                        break;
                    }
                }
                //	Removes ticket count
                else{
                    //	First time running, sets its start time
                    if(temp->checkStart){
                        temp->ready = worldTime;
                        temp->checkStart = false;
                    }
                    temp->running += Q1MAX;
                    worldTime += Q1MAX;
                    temp->tickets -= Q1MAX;
                    temp->runs5++;
                }
                //	Adding new arrive process to the list
                addReadyQ1();

                if(temp->tickets==0)
                    removeQue1(temp);
                else{
                    if(temp->runs5==5){
                        temp->priority--;
                        demoteQ1(temp);
                        temp->runs5 = 0;
                        if(lengthQ1<=0){
                            temp = nullptr;
                            break;
                        }
                    }
                    else{
                        removeQue1(temp);
                        insertQue1(temp);
                    }
                }
                //aging process for queue2
                ageQueue2();
            }
        }

//	Age nodes in queue 2
        void ageQueue2(){
            int itr2 = 0;
            Node* temp2 = headQue2;
            Node* prev;
            int lengthq2 = lengthQ2;
            //	There are nodes to add
            if(lengthq2>0){
                //	Iterates through all the nodes aging them
                while(itr2<lengthq2){
                    prev = temp2;
                    temp2 = temp2->next;
                    aging(prev);
                    itr2++;
                }
            }
        }

//	Checks if and nodes in waiting queue are ready to be added
        void addReadyQ1(){
            int count = 0;
                for(int i=(short)waitQueueT.size()-1;i>=0;i--){
                    if(waitQueueT[i]<=worldTime){
                        count++;
                        Node* tempW = headWaitQueue;
                        while(tempW->arrT!=waitQueueT[i]){
                            tempW = tempW->next;
                        }
                        //	Check which queue the node should be in
                        if(tempW->priority>2){
                            removeWaitQue(tempW);
                            insertQue1(tempW);
                        }
                        else{
                            removeWaitQue(tempW);
                            addQue2(tempW);
                        }
                    }
                }
                if(count>0){
                    for(int i=0; i<count;i++)
                        waitQueueT.pop_back();
                }
        }

//	Serving queue 2
        void servingQ2(){
            int count = 0;
            int checkT = 0;
            Node* temp = headQue2;
            while(lengthQ1==0&&lengthQ2>0){
                checkT = 0;
                temp = headQue2;
                count = 0;
                //	Checks if anything will need to be added to queue in next Q2MAX iterations
                checkT = checkNewArrive();
                //	If something will be added only go up to that point
                if(checkT>0){
                    temp->serveq2 = true;
                    temp->running += (checkT-worldTime);
                    temp->tickets -= (checkT-worldTime);
                    worldTime += (checkT-worldTime);
                    temp->age = 0;
                }
                //	Nothing will be added so run for full amount
                else{
                    //	Less than the possible amount left for tickets
                    if(temp->tickets<=Q2MAX){
                        //	If it hasn't run before
                        if(temp->checkStart){
                            temp->ready = worldTime;
                            temp->checkStart = false;
                        }
                        temp->running += temp->tickets;
                        worldTime += temp->tickets;
                        temp->end = worldTime;
                        temp->tickets = 0;
                    }
                    //	More tickets than what can be dealt with in one operation
                    else{
                        //	If it hasn't been run before
                        if(temp->checkStart){
                            temp->ready = worldTime;
                            temp->checkStart = false;
                        }
                        temp->serveq2 = true;
                        temp->running += Q2MAX;
                        worldTime += Q2MAX;
                        temp->tickets -= Q2MAX;
                        temp->age = 0;
                    }

                }

                //	Adding new process from wait queue
                if(checkT>0){
                    Node* tempW = headWaitQueue;
                    count++;
                    while(tempW->arrT!=checkT){
                        tempW = tempW->next;
                    }
                    //	Add to queue 1
                    if(tempW->priority>2){
                        removeWaitQue(tempW);
                        insertQue1(tempW);
                    }
                    //	Add to queue 2
                    else{
                        removeWaitQue(tempW);
                        addQue2(tempW);
                    }
                }
                if(count>0){
                    for(int i=0; i<count;i++)
                        waitQueueT.pop_back();
                }

                //aging process for queue2
                ageQueue2();

                removeQue2(temp);
                if(temp->tickets>0)
                    addQue2(temp);
            }
        }

// Print both queue, for testing
        void printBoth(){
            std::cout << "Printing Both Queues" << std::endl;
                printQueue1();
                printQueue2();
        }

//	Print only queue 2, for testing
        void printQueue2(){
            std::cout << "Queue 2: Length " << lengthQ2 << std::endl;
            if (lengthQ2>0){
                Node *temp = headQue2;
                printNode(temp);
                temp = temp->next;
                while(temp!=headQue2){
                    printNode(temp);
                    temp = temp->next;
                }
            }
        }

//	Print only queue 1, for testing
        void printQueue1(){
            std::cout << "Queue 1: Length: " << lengthQ1 << std::endl;
            if (lengthQ1>0){
                Node *temp = headQue1;
                printNode(temp);
                temp = temp->next;
                while(temp!=headQue1){
                    printNode(temp);
                    temp = temp->next;
                }
            }
        }

//	Printing a single node
        void printNode(Node* temp){
            std::cout << temp->id << " ";
            std::cout << temp->arrT << " ";
            std::cout << temp->priority << " ";
            std::cout << temp->age << " ";
            std::cout << temp->tickets << " ";
            std::cout << temp->runs5 << std::endl;
        }

//	Print node for websubmittion output
        void printNodeWebSub(Node* temp){
            std::cout << temp->id << " ";
            std::cout << temp->arrT << " ";
            std::cout << temp->end << " ";
            std::cout << temp->ready << " ";
            std::cout << temp->running << " ";
            std::cout << temp->waiting << std::endl;
        }

//	Print in desired form for websubmittion
        void printF(){
            Node *temp = headFinish;
            int count = 0;
            std::cout << "name  arrival     end     ready   running     waiting" << std::endl;
            while(temp!=nullptr&&count<finallist){
                temp->waiting = temp->end - temp->running - temp->ready;
                 printNodeWebSub(temp);
                 temp = temp->next;
                 count++;
            }
        }
};

//	Driver code
int main(int argc,char* argv[]){
    std::ifstream infile(argv[1]);
    std::string line;

    TicketBooker test;
    while(std::getline(infile,line)){
        std::istringstream iss(line);
        test.setUp(line);
    }
//	Deal with all the processes
    test.serving();
//	Print all finished nodes in desired form
    test.printF();
    return 0;
}
