/*
 * =====================================================================================
 *
 *       Filename:  BridgeSort.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/17/17 15:14:43
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
#include <algorithm>
#include <vector>
using namespace std;

class BridgeSort{
    vector<char> compare = {'2','3','4','5','6','7','8',
                           '9','T','J','Q','K','A'};

public:
    string sortedHand(string hand){
        vector<char> Clubs;
        vector<char> Diamonds;
        vector<char> Hearts;
        vector<char> Spades;
        string res = "";

        for(int i=0;i<(int)hand.length();i+=2){
            if(hand[i]=='C')
                Clubs.push_back(hand[i+1]);
            else if(hand[i]=='D')
                Diamonds.push_back(hand[i+1]);
            if(hand[i]=='H')
                Hearts.push_back(hand[i+1]);
            if(hand[i]=='S')
                Spades.push_back(hand[i+1]);
        }


        return sortCard(Clubs,"C")+sortCard(Diamonds,"D")+sortCard(Hearts,"H")+sortCard(Spades,"S");
    }

    string sortCard(vector<char> cards,string suit){
        string result = "";
        if(cards.size()==0)
            return "";
        for(int i=0;i<(int)compare.size();i++){
            bool check = false;
            for(int j=0;j<(int)cards.size();j++){
                if(compare[i]==cards[j]){
                    check = true;
                    break;
                }
            }
            if(check)
                result += suit + compare[i];
        }
        return result;
    }

};
