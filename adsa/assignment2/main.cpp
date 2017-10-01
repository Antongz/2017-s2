/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/07/2017 12:16:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <cctype>
#include <vector>

using namespace std;


class AVLTree{
private:
    struct Node{
        Node* right = nullptr;
        Node* left = nullptr;
        int value = 0;
        int height = 0;
    };
    Node* root = nullptr;

public:

    void setup(string input){
        string temp = "";
        if(isdigit(input[1])&&input[0]=='A'){
            for(int i=1;i<input.length();i++)
                temp += input[i];
            int value = stoi(temp);
            root = insertNode(value,root);
        }else if(isdigit(input[1])&&input[0]=='D'){
            for(int i=1;i<input.length();i++)
                temp += input[i];
            int value = stoi(temp);
            root = deleteNode(value,root);
        }else
            print(input);
    }
    int findMin(Node* node){
        while(node->left!=nullptr)
            node = node->left;
        return node->value;
    }
    int findMax(Node* node){
        while(node->right!=nullptr)
            node = node->right;
        return node->value;
    }

    Node* createNew(int value){
        Node* temp = new Node();
        temp->value = value;
        temp->left = nullptr;
        temp->right = nullptr;
        temp->height = 1;
        return temp;
    }
    Node* insertNode(int value,Node* node){
        if(node==nullptr)
            return createNew(value);
        if(value<node->value)
            node->left = insertNode(value,node->left);
        else if(value>node->value)
            node->right = insertNode(value,node->right);
        else
            return node;

        node->height = max(height(node->left),height(node->right)) + 1;
        int balance = getBalance(node);
        if(balance>1&&value<node->left->value)
            return rightrotate(node);
        if(balance<-1&&value>node->right->value)
            return leftrotate(node);
        if(balance>1&&value>node->left->value){
            node->left = leftrotate(node->left);
            return rightrotate(node);
        }
        if(balance<-1&&value<node->right->value){
            node->right = rightrotate(node->right);
            return leftrotate(node);
        }
        return node;
    }

    Node* deleteNode(int value,Node* node){
        if(node==nullptr)
            return node;
        else if(value<node->value)
            node->left = deleteNode(value,node->left);
        else if(value>node->value)
            node->right = deleteNode(value,node->right);
        //if the value is the same as the root value
        else{
            if(node->value==value&&(node->left==nullptr||node->right==nullptr)){
                Node* temp = node->left? node->left:node->right;
                if(temp==nullptr){
                    temp = node;
                    node = nullptr;
                }else
                    *node = *temp;
                free(temp);
            }else{
                //node with two children
                //Node* temp = minValueNode(node->right);
                Node* temp = maxValueNode(node->left);
                node->value = temp->value;
                //delete the inorder successor:the left subtree of rightmost
                //node->right = deleteNode(temp->value,node->right);
                node->left = deleteNode(temp->value,node->left);
            }
        }

        if(node==nullptr)
            return node;
        node->height = max(height(node->left),height(node->right)) + 1;
        int balance = getBalance(node);

        if(balance>1&&getBalance(node->left)>=0){
            return rightrotate(node);
        }
        if(balance>1&&getBalance(node->left)<0){
            node->left = leftrotate(node->left);
            return rightrotate(node);
        }
        if(balance<-1&&getBalance(node->right)<=0)
            return leftrotate(node);
        if(balance<-1&&getBalance(node->right)>0){
            node->right = rightrotate(node->right);
            return leftrotate(node);
        }
        return node;
    }

    Node* rightrotate(Node* node){
        Node* temp = node->left;
        Node* temp2 = temp->right;
        temp->right = node;
        node->left = temp2;
        node->height = max(height(node->left),height(node->right)) + 1;
        temp->height = max(height(temp->left),height(temp->right)) + 1;
        return temp;
    }
    Node* leftrotate(Node* node){
        Node* temp = node->right;
        Node* temp2 = temp->left;
        temp->left = node;
        node->right = temp2;
        node->height = max(height(node->left),height(node->right)) + 1;
        temp->height = max(height(temp->left),height(temp->right)) + 1;
        return temp;
    }

    Node* maxValueNode(Node* node){
        Node* temp = node;
        while(temp->right!=nullptr)
            temp = temp->right;
        return temp;
    }


    Node* minValueNode(Node* node){
        Node* temp = node;
        while(temp->left!=nullptr)
            temp = temp->left;
        return temp;
    }

    void find(int value,Node* node){
        if(node==nullptr)
            cout << "Can not Find" << endl;
        else{
            if(value<node->value)
                find(value,node->left);
            else{
                if(value>node->value)
                    find(value,node->right);
                else
                    cout << "Element found" << endl;
            }
        }
    }
    int height(Node* node){
        if(node==nullptr)
            return 0;
        return node->height;
    }
    int getBalance(Node* node){
        if(node==nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    int AVLHeight(Node* node){
        return root->height;
    }

    void print(string order){
        if(order=="IN")
            printInorder(root);
        if(order=="PRE")
            printPreorder(root);
        if(order=="POST")
            printPostorder(root);
        if(root==nullptr)
            cout << "EMPTY";
    }

    void printPreorder(Node* node){
        if(node!=nullptr){
            cout << node->value << " ";
            printPreorder(node->left);
            printPreorder(node->right);
        }
    }
    void printInorder(Node* node){
        if(node!=nullptr){
            printInorder(node->left);
            cout << node->value << " ";
            printInorder(node->right);
        }
    }
    void printPostorder(Node* node){
        if(node!=nullptr){
            printPostorder(node->left);
            printPostorder(node->right);
            cout << node->value << " ";
        }
    }
};

int main(){
    vector<string> input; //= //{"A5","A2","A7","A1","A4","A6","A9","A3","A16","A15"};
            //{"A13","A10","A15","A5","A11","A16","A4","A4","A6","A7"};
            //{"A30","A5","A35","A32","A40","A45"};
            //{"A13","A10","A15","A5","A11","A16","A4","A6","A3"};
            //{"A9","A5","A10","A1","A6","A11","A0","A2","A3","D10","D10"};
    AVLTree test;
    string temp;
    while(cin){
        cin >> temp;
        input.push_back(temp);
    }
    for(int i=0;i<input.size()-1;i++){
        test.setup(input[i]);
    }cout << endl;


	return 0;
}
