/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/12/17 12:11:58
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
#include <string>
#include <algorithm>


using namespace std;

class HashTable{
    string status1 = "never used";
    string status2 = "tombstone";
    string statue3 = "occupied";
    vector<string> keys = {"a","b","c","d","e","f","g","h","i","j",
                          "k","l","m","n","o","p","q","r","s","t",
                          "u","v","w","x","y","z"};
    struct Node{
        Node* next = nullptr;
        Node* prev = nullptr;
        string status = "never used";
        string data = "";
    };
    Node* head = nullptr;
    vector<Node*> table;

public:
    HashTable(){
        Node *temp = new Node();
        head = temp;
        table.push_back(temp);
        for(int i=0;i<25;i++){
            Node* temp1 = new Node();
            temp->next = temp1;
            temp1->prev = temp;
            table.push_back(temp1);
            temp = temp->next;
        }
    }
    string searchKey(char input){
        string key = "";
        switch (input) {
        case 'a':
            key = "a";
            break;
        case 'b':
            key = "b";
            break;
        case 'c':
            key = "c";
            break;
        case 'd':
            key = "d";
            break;
        case 'e':
            key = "e";
            break;
        case 'f':
            key = "f";
            break;
        case 'g':
            key = "g";
            break;
        case 'h':
            key = "h";
            break;
        case 'i':
            key = "i";
            break;
        case 'j':
            key = "j";
            break;
        case 'k':
            key = "k";
            break;
        case 'l':
            key = "l";
            break;
        case 'm':
            key = "m";
            break;
        case 'n':
            key = "n";
            break;
        case 'o':
            key = "o";
            break;
        case 'p':
            key = "p";
            break;
        case 'q':
            key = "q";
            break;
        case 'r':
            key = "r";
            break;
        case 's':
            key = "s";
            break;
        case 't':
            key = "t";
            break;
        case 'u':
            key = "u";
            break;
        case 'v':
            key = "v";
            break;
        case 'w':
            key = "w";
            break;
        case 'x':
            key = "x";
            break;
        case 'y':
            key = "y";
            break;
        case 'z':
            key = "z";
            break;
        }
        return key;
    }
    void setup(string input){
        string temp = "";
        for(int i=1;i<(int)input.length();i++)
            temp += input[i];
        if(input[0]=='A'){
            int pos = 0;
            string findKeys = searchKey(input[(int)input.length()-1]);
            bool checkDup = false;
            for(int i=0;i<(int)keys.size();i++){
                if(findKeys==keys[i]){
                    pos = i;
                }
                if(table[i]->data == temp){
                    checkDup = true;
                    break;
                }
            }
            if(checkDup){
                ;
            }else
                addNode(temp,pos);

        }else if(input[0]=='D'){
            int pos = 0;
            string findKeys = searchKey(input[(int)input.length()-1]);
            bool checkIfThere = false;
            for(int i=0;i<(int)keys.size();i++){
                if(findKeys==keys[i]){
                    pos = i;
                }
                if(table[i]->data == temp){
                    pos = i;
                    checkIfThere = true;
                    break;
                }
            }
            if(checkIfThere){
                deleteNode(pos);
            }
        }
    }

    void addNode(string data,int pos){
        Node* temp = table[pos];
        while(true){
            temp = table[pos%26];
            if(table[pos%26]->status==status1||table[pos%26]->status==status2){
                temp->status = statue3;
                temp->data = data;
                break;
            }
            pos++;
        }

    }
    void deleteNode(int pos){
        table[pos]->status = status2;
        table[pos]->data = "";
    }

    void print(){
        for(int i=0;i<26;i++){
            if(table[i]->status==statue3)
                cout << table[i]->data << " ";
        }cout << endl;
    }

};




int main(){
    vector<string> input;
    HashTable test;
    string temp;
    while(cin){
        cin >> temp;
        input.push_back(temp);
    }
    for(int i=0;i<(int)input.size()-1;i++){
        test.setup(input[i]);
    }
    test.print();

	return 0;
}

