/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/03/2017 10:28:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yi-Ting, Hsieh (a1691807), a1691807@student.adelaide.edu.au
 *   Organization:  
 *
 * =====================================================================================
 */


#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;



int main(){
    string I1;
    string I2;
    string Bv;
	cin >> I1;
	cin >> I2;
    cin >> Bv;

    //cout << I1 << " " << I2 << " " << B << endl;
    int B = stoi(Bv);
    if(B<2||B>10){
        cout << "INVALID INPUT" << endl;
        return 0;
    }
	/* set up */
	vector<int> i1Digits;
	vector<int> i2Digits;
    vector<int>	carry;      //for sum school method
	vector<int> sum;
    vector<int> product;
    vector<int> mid;
    vector<int> productMid;
	carry.push_back(0);	//c_0 should always be 0
	/* step1: sum = I1 + I2 ,  using school method */
    int temp1 = 0;
    int temp2 = 0;
    int i1length = I1.length();
    int i2length = I2.length();

    int i = 1;
    int j = 1;
    //int sumR = 0;
	bool check = true;
	int count = 0;
    string a;
    int countBase = 0;
	while(check){
        //sum: school method
        //store the carry
        if(i1length-i>=0||i2length-j>=0){
            //i1Digits.push_back(temp1%10);
            //temp1 = temp1/10;
            //i2Digits.push_back(temp2%10);
            //temp2 = temp2/10;
            if(i1length-i>=0&&i2length-j>=0)
                countBase++;
            if(i1length-i>=0){
                a = I1.at(i1length-i);
                temp1 = stoi(a);
                //cout << temp1 << endl;
                i1Digits.push_back(temp1);
            }
            if(i2length-j>=0){
                a = I2.at(i2length-j);
                //inputSS = new char [2];
                //strcpy(inputSS,i1);
                temp2 = stoi(a);
                i2Digits.push_back(temp2);
            }

            if(count<i1length&&count<i2length){
                sum.push_back((i1Digits[count]+i2Digits[count]+carry[count])%B);
                if((i1Digits[count]+i2Digits[count]+carry[count])<B){
                    carry.push_back(0);
                }else{
                    carry.push_back(1);
                }
            }else{
                if(count<i1length){
                    sum.push_back((i1Digits[count]+carry[count])%B);
                    if(i1Digits[count]+carry[count]<B)
                        carry.push_back(0);
                    else
                        carry.push_back(1);
                }
                if(count<i2length){
                    sum.push_back((i2Digits[count]+carry[count])%B);
                    if(i2Digits[count]+carry[count]<B)
                        carry.push_back(0);
                    else
                        carry.push_back(1);
                }
            }
        }

        count++;
        i++;
        j++;
        /*
		if(temp2<=0&&temp1<=0){
            sum.push_back(carry[count]);
			check = false;
        }*/
        if(i1length-i<0&&i2length-j<0){
            sum.push_back(carry[count]);
            check = false;
        }
	}

    //calculate our sum
    //for(int i=0;i<sum.size();i++){
    //    sumR += sum[i]*(pow(B,i));
    //}
    //cout << "sum is :" << sumR  << " " << I1+I2 << endl;

    //for display sum
    bool checkS = false;
    for(int i=sum.size()-1;i>=0;i--){
        if(checkS)
            cout << sum[i];
        else{
            if(sum[i]!=0){
                checkS = true;
                cout << sum[i];
            }
        }
    }cout << " ";

  //  cout << endl;



	/* step 2: product = I1*I2, using Karatsuba algorithm */
    //in case i1 and i2 size is one
    vector<int> list1;      //store the result for a0b0
    vector<int> list2;      //store the result for a1b1

    /*check size is even/odd for i1 and i2*/
    if(i1Digits.size()%2==1){
        i1Digits.push_back(0);
    }
    if(i2Digits.size()%2==1){
        i2Digits.push_back(0);
    }
    if(i1Digits.size()>=i2Digits.size()){
        if(i1Digits.size()%2==1)
            i1Digits.push_back(0);
    }else{
        if(i2Digits.size()%2==1)
            i2Digits.push_back(0);
    }
    bool checkLength = true;
    if(i1Digits.size()==i2Digits.size()){
        checkLength = false;
    }
    while(checkLength){
        if(i2Digits.size()<i1Digits.size())
            i2Digits.push_back(0);
        else
            i1Digits.push_back(0);

        if(i1Digits.size()==i2Digits.size())
            checkLength = false;
    }
    int maxL = i1Digits.size()*2;
    int klengtha = i1Digits.size()/2;
    int klengthb = i2Digits.size()/2;
    int B2K = (i1Digits.size()+i2Digits.size())/2+1;
    int Bk = B2K/2;
    for(int i=0;i<maxL;i++){
        product.push_back(0);
        productMid.push_back(0);
        mid.push_back(0);
        list1.push_back(0);
        list2.push_back(0);
    }

    //calculate two sub
    int temp3 = 0;
    int temp4 = 0;
    temp1 = 0;
    temp2 = 0;
    //calculate a0*b0
    int ca = 0;
    int countMax = 0;
    int ca2 = 0;
    for(int i=0;i<klengtha;i++){
        temp1 = i1Digits[i+klengtha];
        temp3 = i1Digits[i];
        for(int j=0;j<klengthb;j++){
            ca = 0;
            temp4 = i2Digits[j];
            if((list1[i+j]+temp3*temp4)/B>0){
                ca = (temp3*temp4+list1[i+j])/B;
                list1[i+j+1] += ca;
            }
            list1[i+j] = (list1[i+j]+temp3*temp4)%B;

            ca2 = 0;
            temp2 = i2Digits[j+klengthb];
            if((list2[i+j]+temp1*temp2)/B>0){
                ca2 = (temp1*temp2+list2[i+j])/B;
                list2[i+j+1] += ca2;
            }
            list2[i+j] = (list2[i+j]+temp1*temp2)%B;
        }
    }
    //calculate a1*b1
    /*
    for(int i=klengtha;i<i1Digits.size();i++){
        temp1 = i1Digits[i];
        for(int j=klengthb;j<i2Digits.size();j++){
            ca2 = 0;
            temp2 = i2Digits[j];
            if((list2[i+j-klengtha-klengthb]+temp1*temp2)/B>0){
                ca2 = (temp1*temp2+list2[i+j])/B;
                list2[i+j-klengtha-klengthb+1] += ca2;
            }
            list2[i+j-klengtha-klengthb] = (list2[i+j-klengtha-klengthb]+temp1*temp2)%B;
        }
    }*/;



    /*  a*b = a1*b1*B^2k + ((a1+a0)*(b1+b0)-(a1b1+a0b0))*B^k + a0b0 */
    temp1 = 0;  temp2 = 0;
    int temRes = 0;
    countMax = 0;
    ca = 0;
    int baseMi = 0;
    int baseMj = 0;
    vector<int> helpMid;
    for(int i=0;i<4;i++){
        helpMid.push_back(0);
    }
    /*calculate the result for (a1+a0)*(b1+b0)*/
    for(int i=0;i<klengtha;i++){
        baseMi = 1;
        temp1 = (i1Digits[i]+i1Digits[i+klengtha]);
        if(temp1/B>0){
            baseMi++;
        }
        for(int j=0;j<klengthb;j++){
            for(int k=0;k<4;k++){
                helpMid[k] = 0;
            }
            baseMj = 1;
            temp2 = i2Digits[j]+i2Digits[j+klengthb];
            temRes = temp1*temp2;
            int tempItr = 0;
            if(temp2/B>0){
                baseMj++;
            }
            while(tempItr<baseMi+baseMj){
                helpMid[tempItr] = temRes%B;
                mid[i+j+tempItr] += helpMid[tempItr];
                if(mid[i+j+tempItr]/B>0){
                    mid[i+j+tempItr+1] += mid[i+j+tempItr]/B;
                    mid[i+j+tempItr] = mid[i+j+tempItr]%B;
                }
                temRes = temRes/B;
                tempItr++;
            }


            //store the value for the result of (a1+a0)*(b1+b0)
        }
    }
    if(mid[mid.size()-1]==0)
        mid.pop_back();
/*
    cout << "list1: ";
    for(int i=list1.size()-1;i>=0;i--){
        cout << list1[i] << " ";
    }cout << endl;

    cout << "Mid: ";
    for(int i=mid.size()-1;i>=0;i--){
        cout << mid[i] << " ";
    }cout << endl;

    cout << "list2: ";
    for(int i=list2.size()-1;i>=0;i--){
        cout << list2[i] << " ";
    }cout << endl;
*/
    //calculate (a1b1+a0b0) : productmid
    temp1 = 0;
    temp2 = 0;
    int itr = 0;
    int countM = 0;
    bool checkM = true;
    for(int i=0;i<list1.size();i++){
        temp1 = list1[i];
        temp2 = list2[i];
        if((temp1+temp2+productMid[i])/B>0){
            productMid[i+1] = ((temp1+temp2+productMid[i])/B)+productMid[i+1];
        }
        productMid[i] = ((productMid[i]+temp1+temp2)%B);
    }

    //result for: ((a1+a0)*(b1+b0)-(a1b1+a0b0))
    if(mid.size()<productMid.size()){
        int updateM = productMid.size()-mid.size();
        while(updateM>0){
            mid.push_back(0);
            updateM--;
        }
    }
    if(mid.size()>productMid.size()){
        int updateM = mid.size()-productMid.size();
        while(updateM>0){
            productMid.push_back(0);
            updateM--;
        }
    }


    //calculate (a1+a0)(b1+b0)-(a1b1+a0b0)
    checkM = false;
    itr = 0;
    for(int i=mid.size()-1;i>=0;i--){
        if(mid[i]>=productMid[i])
            mid[i]=mid[i]-productMid[i];
        else{
            //2conditions
            if(mid[i+1]==0){
                checkM = true;
                itr = i+1;
                while(checkM){
                    mid[itr]=B-1;
                    itr++;
                    if(mid[itr]>0){
                        mid[itr]--;
                        checkM=false;
                    }
                }
                mid[i]=mid[i]+B-productMid[i];
            }else{
                mid[i+1]--;
                mid[i]=mid[i]+B-productMid[i];
            }
        }
    }
    if(mid[mid.size()-1]/B>0){
        mid.push_back(mid[mid.size()-1]/B);
        mid[mid.size()-2]=mid[mid.size()-2]%B;
    }

    for(int i=0;i<mid.size();i--){
        if(mid[i]>=B){
            mid[i+1] += mid[i]/B;
            mid[i] = mid[i]%B;
        }
    }


    //cout << "klengtha: " << klengtha << " " << "list1size: " << list1.size() << endl;
    //cout << "klengthb: " << klengthb << " " << "list2size: " << list2.size() << endl;
/*    cout << "productmid: ";
    for(int i=productMid.size()-1;i>=0;i--){
        cout << productMid[i] << " ";
    }cout << endl;

    cout << "MidAfter: ";
    for(int i=mid.size()-1;i>=0;i--){
        cout << mid[i] << " ";
    }cout << endl;

*/

    /*combine the result: a*b = a1b1*B^2k + midterm*B^k + a0b0 */
    B2K = (klengtha+klengthb);
    if(B2K%2==1)
        Bk = B2K/2+1;
    else
        Bk = B2K/2;

    itr = 0;
    temp1 = 0;
   // cout << "list1: " << list1.size() << " list2: " << list2.size() << " mid: " << mid.size()  << " maxL: " << maxL << endl;
    //cout << "klengtha: " << klengtha << " klengthb: " << klengthb << endl;
    //cout << "Bk: " << Bk << " B2K: " << B2K << endl;
    //cout << "countBase " << countBase << endl;
    while(itr<maxL){
        temp1 = 0;
        if(itr<list1.size()){
            temp1 += list1[itr];
        }
        if(itr>=Bk&&itr<Bk+mid.size()){
            temp1 += mid[itr-Bk];
        }
        if(itr>=B2K&&itr<B2K+list2.size()){
            temp1 += list2[itr-B2K];
        }

        temp1 = (temp1+product[itr]);
        product[itr] = temp1%B;
        if(temp1/B>0){
            product[itr+1] = temp1/B;
        }
        itr++;
    }



    //display our product
    bool checkP = false;
    for(int i=product.size()-1;i>=0;i--){
        if(checkP)
            cout << product[i];
        else{
            if(product[i]!=0){
                checkP = true;
                cout << product[i];
            }
        }
    }cout << endl;


    return 0;
}
