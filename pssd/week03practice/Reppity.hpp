/*
 * =====================================================================================
 *
 *       Filename:  Reppity.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/21/2017 01:10:33 AM
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

using namespace std;

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Reppity {
    public:
    int longestRep(string s) {
        for (int len=(int)s.size()/2; len>0; --len){
            for (int i=0; i+2*len<=(int)s.size(); ++i){
                if (s.substr(i+len).find(s.substr(i, len)) != string::npos)
                    return len;

            }
        }
        return 0;
    }
};




