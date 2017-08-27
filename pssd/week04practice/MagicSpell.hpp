/*
 * =====================================================================================
 *
 *       Filename:  MagicSpell.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/22/2017 02:27:59 PM
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

using namespace std;
class MagicSpell{

    public:
        string fixTheSpell(string spell){
            int itr = 0;
            string res = spell;
            string a = "a";
            string z = "z";
            vector<int> list;
            while(itr<spell.length()){

                if(spell[itr]=='a'||spell[itr]=='z'||spell[itr]=='A'||spell[itr]=='Z')
                    list.push_back(itr);
                itr++;
            }

            for(int i=0;i<list.size()/2;i++){
                int temp1 = list[i];
                int temp2 = list[list.size()-1-i];
                char temp = res[temp1];
                res[temp1] = res[temp2];
                res[temp2] = temp;
            }

            return res;
        }
};
