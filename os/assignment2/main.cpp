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
    int eventTrace = 0;         //counting #events
    int readDisk = 0;           //counting #disk reads
    int writeDisk = 0;          //counting #disk writes
    int preFetchFaults = 0;     //counting #prefetch faults for wsarb
    int pageFaults = 0;         //counting #page faults
    int pageSize = 0;           //store our page sizes
    int numberOfPage = 0;       //the number of page frames in simulated memory
    string algorithm = "";      //store which algorithm we're going to use
    string mode = "";           //store which mode we're going to print: quiet/debug
    bool debug = false;
    int curPID = 0;             //store our current process id
    int curLength = 0;          //current length of our list
    int ARB = 0;                //store the ARB value
    int workingSets = 0;        //store the size of working set
    int counter = 0;            //to decide when to shift our arb registers
    bool checkFirst = true;     //just for wsarb, checking the first process
    int curWorkingSets = 0;     //counting #current working sets
    struct Node{
        Node* next = nullptr;
        Node* prev = nullptr;
        string wr;              //check read or write
        long long memoryAd;     //store memory address
        long long pageID;       //store the pageID
        long long arb8Bits = 0; //store our arb to longlong value
        string arb = "00000000";//store the page's 8bits registers
        int reference = 1;      //our reference bit
        bool checkWS = false;   //for checking our working set node
        int countWS = 0;        //for counting how long it's been stayed
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* WShead = nullptr;
    Node* WStail = nullptr;
    /*I use a hash table to stores our working sets*/
    vector<int> processID;      //our key of the hashing table
    vector<int> processLength;  //stores the length of working sets nodes
    vector<Node*> process;      //store our table with(key=processID[k])
    vector<Node*> processTail;

    //this is the fifo algorithm: queue structure
    //it will always replace the page that has been resident in memory longest.
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
            pageFaults++;
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

    //this is the arb algorithm
    //use 8-bits shift register and one reference bit to approximate a LRU scheme.
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
            pageFaults++;
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


    //this is the wsarb algorithm
    //basically, it's the same as arb algorithm.
    //but it keep tracking and storing our working sets pages.
    void wsarb(string demand){
        Node* temp = new Node();
        setMemAndWR(temp,demand);
        Node* WSitr;
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
            //WSitr = copyLink(itr);
        }else{
            readDisk++;
            pageFaults++;
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
            //WSitr = copyLink(temp);
        }

        //shift arb
        counter++;
        if(counter==ARB){
            counter = 0;
            itr = head;
            while(itr!=nullptr){
                shiftNodeARB(itr);
                itr = itr->next;
            }
        }

        //test for working set models
        //cout << WSitr->pageID << endl;
        //updateWSet();
        WSitr = copyLink(temp);
        addWSNode(WSitr);
        shiftWS();
        if(curWorkingSets>workingSets)
            cout << "curworkingsets size is bigger than workingsets size" << endl;
    }

    //adding a new page to our pages
    void addNew(Node* temp){
        //temp->prev = nullptr;
        if(curLength==0){
            head = temp;
            tail = temp;
            curLength++;
        }else{
            curLength++;
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }
    //remove a page from our pages table
    void removeNode(Node* node){
        curLength--;
        if(head==node&&tail==node){
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
    //if the page got reference, and the new instructions is writing mode,
    //then you change our node to writing mode
    void changeSamePage(Node* node){
        node->wr = "W";
    }
    //seting up the node corresponds to our memory address and other information
    void setMemAndWR(Node* node,string demand){
        node->wr = demand[0];
        string temp;
        for(int i=2;i<(int)demand.length();i++)
            temp += demand[i];
        node->memoryAd = HexToDecimal(temp);
        setPageId(node);
    }
    //given a string of hexidecimal value, and return the longlong type of that value
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
    //setting our node's pageID, which is the number of that pages.
    void setPageId(Node* node){
        long long temp = node->memoryAd;
        node->pageID = temp/pageSize;
        //cout << "pageid" << node->pageID << endl;

    }
    //if the page just got reference, set the reference bit to 1
    void pageGetReference(Node* node){
        node->reference = 1;
        node->countWS = 0;
    }
    //shift the 8bit registers of our pages table, for arb and wsarb
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
    //just for debuging
    void printCurPageTable(){
        Node* itr = tail;
        cout << "print current table" << endl;
        while(itr!=nullptr){
            cout << itr->pageID << " ";
            itr = itr->prev;
        }cout << endl;
    }
    //add a new node to our working set
    void addWSNode(Node* node){
        Node* itr = WShead;
        bool checkIfInPages = false;
        while(itr!=nullptr){
            if(itr->pageID==node->pageID){
                checkIfInPages = true;
                break;
            }
            itr = itr->next;
        }
        curWorkingSets++;
        if(WShead==nullptr&&WStail==nullptr){
            WShead = node;
            WStail = node;
        }else{
            node->next = WShead;
            WShead->prev = node;
            WShead = node;
            if(checkIfInPages){
                removeWSNode(itr);
            }
        }
    }
    //decide which nodes we need to remove from our working sets
    void removeWS(){
        Node* itr = WStail;
        while(itr!=nullptr){
            Node* temp = itr;
            itr = itr->prev;
            if(temp->countWS>workingSets){
                //cout << temp->pageID << " " << temp->countWS << " " << curWorkingSets << endl;
                removeWSNode(temp);
            }
        }//cout << endl;
    }
    //just for debuging
    void printCurSet(Node* tempH){
        cout << "current working set" << endl;
        while(tempH!=nullptr){
            cout << tempH->pageID << " ";
            tempH = tempH->next;
        }cout << endl;
    }
    //remove the working set nodes
    void removeWSNode(Node* node){
        curWorkingSets--;
        if(node==WShead&&node==WStail){
            WShead = nullptr;
            WStail = nullptr;
            curWorkingSets = 0;
        }else if(node==WShead){
            WShead = node->next;
            WShead->prev = nullptr;
        }else if(node==WStail){
            WStail = node->prev;
            WStail->next = nullptr;
        }else{
            Node* tempP = node->prev;
            Node* tempN = node->next;
            tempP->next = tempN;
            tempN->prev = tempP;
        }
        node->prev = nullptr;
        node->next = nullptr;
    }
    //implement our wsarb to shift the counter
    void shiftWS(){
        Node* itr = WShead;
        while(itr!=nullptr){
            itr->countWS++;
            itr = itr->next;
        }
        removeWS();
        //test
        itr = head;
        while(itr!=nullptr){
            itr->countWS++;
            itr = itr->next;
        }
    }
    //update our node's value in working set with the current pages table
    void updateWSet(){
        Node* itr = head;
        Node* itr2 = WShead;
        while(itr2!=nullptr){
            itr = head;
            while(itr!=nullptr){
                if(itr2->pageID==itr->pageID){
                    itr2->arb8Bits = itr->arb8Bits;
                    itr2->arb = itr->arb;
                    itr2->reference = itr->reference;
                    itr2->wr = "R";
                    break;
                }
                itr = itr->next;
            }
            itr2 = itr2->next;
        }
    }
    //copy a new node for working set models
    Node* copyLink(Node* oldNode){
        Node* temp = new Node();
        temp->arb = oldNode->arb;
        temp->arb8Bits = oldNode->arb8Bits;
        temp->wr = oldNode->wr;
        temp->memoryAd = oldNode->memoryAd;
        temp->pageID = oldNode->pageID;
        temp->reference = oldNode->reference;
        temp->countWS = oldNode->countWS;
        temp->prev = nullptr;
        temp->next = nullptr;
        return temp;
    }

public:
    //setting our page information
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
                ;//printCurPageTable();
            }
            else if(this->algorithm=="wsarb"){
                //cout << curWorkingSets << endl;
                if(checkFirst){
                    //cout << "working set size " << workingSets << endl;
                    checkFirst = false;
                    WShead = nullptr;
                    WStail = nullptr;
                    curWorkingSets = 0;
                    string tempPID;
                    for(int i=2;i<(int)demand.length();i++){
                        if(demand[i]==' ')
                            break;
                        tempPID += demand[i];
                    }
                    int newPID = stoi(tempPID);     //store our new process ID
                    curPID = newPID;
                    //cout << "pid: " << curPID << endl;
                }else{
                    //cout << "current pid:" << curPID << endl;
                    //printCurPageTable();
                    //printCurSet(WShead);
                    updateWSet();

                    //store the current state
                    //check whether the state is already in our working set
                    bool checkStoreInWS = false;
                    int posR = 0;
                    for(int i=0;i<(int)processID.size();i++){
                        if(processID[i]==curPID){
                            posR = i;
                            process[i] = WShead;
                            processTail[i] = WStail;
                            processLength[i] = curWorkingSets;
                            checkStoreInWS = true;
                            break;
                        }
                    }
                    if(checkStoreInWS){
                        ;//cout << "update the page for: " << processID[posR] << " " << processLength[posR] << endl;
                    }else{
                        //cout << "store new pages for " << curPID << endl;
                        processID.push_back(curPID);
                        processLength.push_back(curWorkingSets);
                        processTail.push_back(WStail);
                        process.push_back(WShead);
                    }


                    //then we check the new arrive process is in our working set
                    string tempPID;
                    for(int i=2;i<(int)demand.length();i++){
                        if(demand[i]==' ')
                            break;
                        tempPID += demand[i];
                    }
                    int newPID = stoi(tempPID);     //store our new process ID
                    //cout << "new pid is: " << newPID << endl;
                    //check whether the new process ID is already in our working set
                    bool checkIfInWorkingSet = false;
                    int pos = 0;
                    for(int i=0;i<(int)processID.size();i++){
                        if(processID[i]==newPID){
                            //cout << "we've found out pages, need to do the content switch to this page " << newPID  << endl;
                            pos = i;
                            checkIfInWorkingSet = true;
                            break;
                        }
                    }

                    //if our new process is already in our working set
                    //we need to load the pages
                    if(checkIfInWorkingSet){
                        //store our current state first
                        //load the working set
                        WShead = process[pos];
                        WStail = processTail[pos];
                        curWorkingSets = processLength[pos];
                        Node* itr = tail;
                        Node* itrWs = WStail;
                        while(itrWs!=nullptr){
                            itr = tail;
                            while(itr!=nullptr){
                                if(itrWs->pageID==itr->pageID){
                                    itr->checkWS = true;
                                    itrWs->checkWS = true;
                                }
                                itr = itr->prev;
                            }
                            itrWs = itrWs->prev;
                        }

                        itr = tail;
                        itrWs = WShead;
                        Node* tempR = tail;

                        while(itrWs!=nullptr){
                            itr = tail;
                            tempR = tail;
                            if(itrWs->checkWS==false){
                                readDisk++;
                                preFetchFaults++;
                                while(itr!=nullptr){
                                    if(tempR->arb8Bits>itr->arb8Bits
                                            &&itr->reference==0&&itr->checkWS==false)
                                        tempR = itr;
                                    else if(tempR->reference==1&&itr->reference==1&&
                                            tempR->arb8Bits>itr->arb8Bits&&itr->checkWS==false)
                                        tempR = itr;

                                    itr = itr->prev;
                                }
                                //cout << "prepaging, replace: " << tempR->pageID << " to " << itrWs->pageID << endl;
                                if(tempR->wr=="W"){
                                    writeDisk++;
                                }
                                removeNode(tempR);
                                Node* tempNew = copyLink(itrWs);
                                tempNew->checkWS = true;
                                //tempNew->reference = 1;
                                //tempNew->arb8Bits = 0;
                                //tempNew->arb = "00000000";
                                addNew(tempNew);
                            }
                            itrWs = itrWs->next;
                        }

                        itr = tail;
                        itrWs = processTail[pos];
                        while(itrWs!=nullptr){
                            itrWs->checkWS = false;
                            itrWs = itrWs->prev;
                        }
                        while(itr!=nullptr){
                            itr->checkWS = false;
                            itr = itr->prev;
                        }

                        //cout << "after prepaging" << endl;
                        //printCurPageTable();
                        //printCurSet(WShead);
                        //WShead = nullptr;
                        //WStail = nullptr;
                        //curWorkingSets = 0;
                        curPID = newPID;
                    }

                    //the process is not in working set
                    //set up for the new/old proceess
                    else{
                        WShead = nullptr;
                        WStail = nullptr;
                        curWorkingSets = 0;
                        curPID = newPID;
                    }
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

    //print out our result
    void print(){
        printQuiet();
    }
    void printQuiet(){
        cout << "events in trace: " << eventTrace << endl;
        cout << "total disk reads: " << readDisk << endl;
        cout << "total disk writes: " << writeDisk << endl;
        cout << "page faults: " << pageFaults << endl;
        cout << "prefetch faults: " << preFetchFaults << endl;
    }

    void setARB(string arb){
        ARB = stoi(arb);
    }
    //setting our working set arb register
    void setWSARB(string arb,string workingSize){
        ARB = stoi(arb);
        workingSets = stoi(workingSize);
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
