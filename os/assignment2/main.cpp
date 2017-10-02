/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/22/2017 03:12:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctype.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <utility>

using namespace std;

class Page{

    int eventTrace = 0;
    int readDisk = 0;
    int writeDisk = 0;
    int preFetchFaults = 0;
    int pageSize = 0;
    int numberOfPage = 0;       //the number of page frames in simulated memory
    string algorithm = "";
    string mode = "";
    bool debug = false;
    int curPID = 0;
    int curLength = 0;          //current length of our list
    int ARB = 0;                //store the ARB value
    int workingSets = 0;        //store the size of working set
    int curWorkingSets = 0;
    int counter = 0;
    bool checkFirst = true;
    struct Node{
        Node* next = nullptr;
        Node* prev = nullptr;
        string wr;              //check read or write
        long long memoryAd;     //store memory address
        long long pageID;       //store the pageID
        long long arb8Bits = 0; //for additional arb8Bits bit
        string arb = "00000000";
        int reference = 1;
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    string PIDandCom = "";
    vector<int> processID;
    vector<int> processLength;
    vector<Node*> process;
    vector<Node*> processTail;

public:
    Page(string mode,string PageSize,string numberOfPage,string algorithm){
        this->mode = mode;
        if(mode=="debug")
            debug = true;
        this->pageSize = stoi(PageSize);
        this->numberOfPage = stoi(numberOfPage);
        this->algorithm = algorithm;
    }
    //demand:W 0000000
    void deMandPage(string demand){
        //e.g # 0 test1
        //      pid command
        if(demand[0]=='#'){
            if(this->algorithm=="fifo"||this->algorithm=="arb"){
                ;
            }else if(this->algorithm=="wsarb"){
                if(checkFirst){
                    checkFirst = false;
                }else{
                //store the current state
                //check whether the state is already in the our working set
                    bool checkStoreInWS = false;
                    for(int i=0;i<(int)processID.size();i++){
                        if(processID[i]==curPID){
                            process[i] = head;
                            processTail[i] = tail;
                            processLength[i] = curLength;
                            checkStoreInWS = true;
                            break;
                        }
                    }
                    if(checkStoreInWS)
                        ;
                    else{
                        processID.push_back(curPID);
                        processLength.push_back(curLength);
                        processTail.push_back(tail);
                        process.push_back(head);
                    }
                }

                //then we check the new arrive process is in our working set
                string tempPID;
                for(int i=2;i<(int)demand.length();i++){
                    if(demand[i]==' ')
                        break;
                    tempPID += demand[i];
                }
                int newPID = stoi(tempPID);     //store our new process ID
                //check whether the new process ID is already in our working set
                bool checkIfInWorkingSet = false;
                for(int i=0;i<(int)processID.size();i++){
                    if(processID[i]==newPID){
                        checkIfInWorkingSet = true;
                        break;
                    }
                }
                curWorkingSets++;

                //if our new process is already in our working set
                //we need to load the pages
                if(checkIfInWorkingSet){
                    //store our current state first
                    if(curWorkingSets>workingSets)
                        curWorkingSets = workingSets;
                    //load the working set
                    int pos = 0;
                    for(int i=0;i<(int)processID.size();i++){
                        if(newPID==processID[i]){
                            pos = i;
                            head = process[i];
                            tail = processTail[i];
                            curLength = processLength[i];
                            curPID = processID[i];
                            break;
                        }
                    }
                    //swap our pages to the last of our queue
                    for(int i=pos;i<(int)processID.size()-1;i++){
                        swap(processID[i],processID[i+1]);
                        swap(process[i],process[i+1]);
                        swap(processTail[i],processTail[i+1]);
                        swap(processLength[i],processLength[i+1]);
                    }
                }
                //the process is not in working set
                //set up for the new/old proceess
                else{
                    if(curWorkingSets>workingSets){
                        curWorkingSets = workingSets;
                        vector<int> tempProcessID;
                        vector<int> tempProcessLength;
                        vector<Node*> tempProcess;
                        vector<Node*> tempProcessTail;
                        for(int i=1;i<(int)processID.size();i++){
                            tempProcessID.push_back(processID[i]);
                            tempProcessLength.push_back(processLength[i]);
                            tempProcess.push_back(process[i]);
                            tempProcessTail.push_back(processTail[i]);
                        }
                        processID = tempProcessID;
                        process = tempProcess;
                        processTail = tempProcessTail;
                        processLength = tempProcessLength;
                    }
                    curPID = newPID, head = nullptr, tail = nullptr, curLength = 0;
                }
            }

        }else if(demand[0]=='W'||demand[0]=='R'){
            eventTrace++;
            if(this->algorithm=="fifo")
                fifo(demand);
            else if(this->algorithm=="arb")
                arb(demand);
            else if(this->algorithm=="wsarb")
                wsarb(demand);
        }
    }

    void fifo(string demand){
        Node* temp = new Node();
        setMemAndWR(temp,demand);
        bool ifInPage = false;
        Node* itr = head;
        while(itr!=nullptr){
            if(itr->pageID==temp->pageID){
                ifInPage = true;
                break;
            }
            itr = itr->next;
        }
        //If the new demand in our pages
        if(ifInPage){
            if(debug)
                cout << "HIT: " << "page " << temp->pageID << endl;
            itr = head;
            while(itr->pageID!=temp->pageID)
                itr = itr->next;
            if(temp->wr=="W")
                changeSamePage(itr);
        }else{
        //If the new demand is not in our pages
            readDisk++;
            if(debug)
                cout << "MISS: " << "page " << temp->pageID << endl;
            if(curLength==0){
                head = temp;
                tail = temp;
                curLength++;
            }else if(curLength<numberOfPage){
                temp->next = head;
                head->prev = temp;
                head = temp;
                curLength++;
            }else{
                if(debug){
                    if(tail->wr=="W"){
                        writeDisk++;
                        cout << "REPLACE: " << "page " << tail->pageID <<" (DIRTY)" << endl;
                    }else
                        cout << "REPLACE: " << "page " << tail->pageID << endl;
                }else{
                    if(tail->wr=="W")
                        writeDisk++;
                }
                if(itr==nullptr){
                    tail = tail->prev;
                    tail->next = nullptr;
                    temp->next = head;
                    head->prev = temp;
                    head = temp;
                }
                //curLength++;
            }
        }

    }

    void arb(string demand){
        Node* temp = new Node();
        setMemAndWR(temp,demand);
        bool ifInPage = false;
        Node* itr = head;
        while(itr!=nullptr){
            if(itr->pageID==temp->pageID){
                ifInPage = true;
                break;
            }
            itr = itr->next;
        }
        //If the new demand is already in our pages table
        if(ifInPage){
            if(debug)
                cout << "HIT: " << "page " << temp->pageID << endl;
            itr = head;
            while(itr->pageID!=temp->pageID)
                itr = itr->next;
            if(temp->wr=="W"){
                changeSamePage(itr);
                pageGetReference(itr);
            }else{       
                pageGetReference(itr);
            }
        }else{
        //If the new demand is not in our pages
            readDisk++;
            if(debug)
                cout << "MISS: " << "page " << temp->pageID << endl;
            if(curLength==0){
                head = temp;
                tail = temp;
                curLength++;
            }else if(curLength<numberOfPage){
                temp->next = head;
                head->prev = temp;
                head = temp;
                curLength++;
            }else{
                //we need to replace the page
                Node* tempD = tail;
                Node* tempR = tail;

                while(tempD!=nullptr){
                    if(tempD->arb8Bits==0&&tempD->reference==0){
                        tempR = tempD;
                        break;
                    }
                    if(tempD->arb8Bits<tempR->arb8Bits&&tempD->reference==0)
                        tempR = tempD;
                    tempD = tempD->prev;
                }
                if(debug){
                    if(tempR->wr=="W"){
                        writeDisk++;
                        cout << "REPLACE: " << "page " << tempR->pageID <<" (DIRTY)" << endl;
                    }else
                        cout << "REPLACE: " << "page " << tempR->pageID << endl;
                }else{
                    if(tempR->wr=="W")
                        writeDisk++;
                }
                removeNode(tempR);
                addNew(temp);
            }
        }
        //test
        counter++;
        if(counter==ARB){
            counter = 0;
            itr = head;
            while(itr!=nullptr){
                shiftNodeARB(itr);
                itr = itr->next;
            }
        }
    }
    void wsarb(string demand){
        Node* temp = new Node();
        setMemAndWR(temp,demand);

        bool ifInPage = false;
        Node* itr = head;
        while(itr!=nullptr){
            if(itr->pageID==temp->pageID){
                ifInPage = true;
                break;
            }
            itr = itr->next;
        }
        //If the new demand is already in our pages table
        if(ifInPage){
            if(debug)
                cout << "HIT: " << "page " << temp->pageID << endl;
            itr = head;
            while(itr->pageID!=temp->pageID)
                itr = itr->next;
            if(temp->wr=="W"){
                changeSamePage(itr);
                pageGetReference(itr);
            }else{
                pageGetReference(itr);
            }
        }else{
        //If the new demand is not in our pages
            //check whether it is in other process
            Node* checkW;
            bool checkIn = false;

            for(int i=0;i<(int)processID.size();i++){
                checkW = process[i];
                checkIn = false;
                if(curPID!=processID[i]){
                    while(checkW!=nullptr){
                        if(checkW->pageID==temp->pageID){
                            removeNodeWsarb(checkW,i);
                            checkIn = true;
                            break;
                        }
                        checkW = checkW->next;
                    }
                }
                if(checkIn){
                    break;
                }

            }

            if(checkIn){
                preFetchFaults++;
                if(checkW->wr=="W")
                    temp->wr = "W";
            }else
                readDisk++;
            if(debug)
                cout << "MISS: " << "page " << temp->pageID << endl;
            if(curLength==0){
                head = temp;
                tail = temp;
                curLength++;
            }else if(curLength<numberOfPage){
                temp->next = head;
                head->prev = temp;
                head = temp;
                curLength++;
            }else{
                //we need to replace the page
                Node* tempD = tail;
                Node* tempR = tail;

                while(tempD!=nullptr){
                    if(tempD->arb8Bits==0&&tempD->reference==0){
                        tempR = tempD;
                        break;
                    }
                    if(tempD->arb8Bits<tempR->arb8Bits&&tempD->reference==0)
                        tempR = tempD;
                    tempD = tempD->prev;
                }
                if(debug){
                    if(tempR->wr=="W"){
                        writeDisk++;
                        cout << "REPLACE: " << "page " << tempR->pageID <<" (DIRTY)" << endl;
                    }else
                        cout << "REPLACE: " << "page " << tempR->pageID << endl;
                }else{
                    if(tempR->wr=="W")
                        writeDisk++;
                }
                removeNode(tempR);
                addNew(temp);
            }
        }
        //test
        counter++;
        if(counter==ARB){
            counter = 0;
            itr = head;
            while(itr!=nullptr){
                shiftNodeARB(itr);
                itr = itr->next;
            }
        }
    }
    void removeNodeWsarb(Node* node,int pos){
        if(node==process[pos])
            process[pos] = node->next;
        if(node==processTail[pos])
            processTail[pos] = node->prev;
        Node* tempN = node->next;
        Node* tempP = node->prev;
        tempP->next = tempN;
        tempN->prev = tempP;
        node->prev = nullptr;
        node->next = nullptr;
        processLength[pos]--;
    }
    void secondChance(Node* node){
        string newShiftBit = "10000000";
        node->arb = newShiftBit;
        node->arb8Bits = HexToDecimal(node->arb);
        node->reference = 0;
    }
    void changeSamePage(Node* node){
        node->wr = "W";
    }
    void addNew(Node* temp){
        //temp->prev = nullptr;
        if(curLength==0){
            head = temp;
            tail = temp;
            curLength++;
        }else{
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }
    void removeNode(Node* node){
        if(head==node&&tail==node&&curLength==1){
            curLength = 0;
            head = nullptr;
            tail = nullptr;
        }else if(node==tail){
            tail = node->prev;
            tail->next = nullptr;
        }else if(node==head){
            head = node->next;
            head->prev = nullptr;

        }else{
            Node* tempP = node->prev;
            Node* tempN = node->next;
            tempP->next = tempN;
            tempN->prev = tempP;
        }
        node->prev = nullptr;
        node->next = nullptr;
    }

    void setMemAndWR(Node* node,string demand){
        node->wr = demand[0];
        string temp;
        for(int i=2;i<(int)demand.length();i++)
            temp += demand[i];
        node->memoryAd = HexToDecimal(temp);
        setPageId(node);
    }
    long long HexToDecimal(string hex){
        long long temp = 0;
        int itr = 0;
        while(itr<(int)hex.length()){
            switch(hex[itr]){
            case '0':
                temp = temp*16 + 0;
                break;
            case '1':
                temp = temp*16 + 1;
                break;
            case '2':
                temp = temp*16 + 2;
                break;
            case '3':
                temp = temp*16 + 3;
                break;
            case '4':
                temp = temp*16 + 4;
                break;
            case '5':
                temp = temp*16 + 5;
                break;
            case '6':
                temp = temp*16 + 6;
                break;
            case '7':
                temp = temp*16 + 7;
                break;
            case '8':
                temp = temp*16 + 8;
                break;
            case '9':
                temp = temp*16 + 9;
                break;
            case 'a':
                temp = temp*16 + 10;
                break;
            case 'b':
                temp = temp*16 + 11;
                break;
            case 'c':
                temp = temp*16 + 12;
                break;
            case 'd':
                temp = temp*16 + 13;
                break;
            case 'e':
                temp = temp*16 + 14;
                break;
            case 'f':
                temp = temp*16 + 15;
                break;
            }
            itr++;
        }
        //cout << "hextoDec " << temp << endl;
        return temp;
    }
    void setPageId(Node* node){
        long long temp = node->memoryAd;
        node->pageID = temp/pageSize;
        //cout << "pageid" << node->pageID << endl;

    }
    void print(){
        printQuiet();
    }
    void printQuiet(){
        cout << "events in trace: " << eventTrace << endl;
        cout << "total disk reads: " << readDisk << endl;
        cout << "total disk writes: " << writeDisk << endl;
        cout << "page faults: " << readDisk-preFetchFaults << endl;
        cout << "prefetch faults: " << preFetchFaults << endl;
    }
    void setARB(string arb){
        ARB = stoi(arb);
    }
    void setWSARB(string arb,string workingSize){
        ARB = stoi(arb);
        workingSets = stoi(workingSize);
    }
    void pageGetReference(Node* node){
        node->reference = 1;
    }
    void shiftNodeARB(Node* node){
        if(node->reference==1){
            string newShiftBit = "1";
            for(int i=0;i<7;i++)
                newShiftBit += node->arb[i];
            node->arb = newShiftBit;
            node->arb8Bits = HexToDecimal(node->arb);
            node->reference = 0;
        }else{
            string newShiftBit = "0";
            for(int i=0;i<7;i++)
                newShiftBit += node->arb[i];
            node->arb = newShiftBit;
            node->arb8Bits = HexToDecimal(node->arb);
        }
    }


};


//input argument: filename, mode(quiet/debug), page/frame size, number of page frames in simulated memory, fifo/arb/wsarb)
int main(int argc,char* argv[]){
	ifstream infile(argv[1]);
	string line;

    Page test(argv[2],argv[3],argv[4],argv[5]);
    string alg = argv[5];
    if(alg=="arb")
        test.setARB(argv[6]);
    if(alg=="wsarb")
        test.setWSARB(argv[6],argv[7]);

	while(getline(infile,line)){
		istringstream iss(line);
        //cout << line << endl;
        test.deMandPage(line);
	}
    test.print();

    return 0;
}
