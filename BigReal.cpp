#include "BigReal.h"

#include <bits/stdc++.h>

using namespace std;

BigReal::BigReal():sign('+') , integer("0") , decimal("0"),fullRealNumber("+0.0"){
}

BigReal::BigReal(std::string str) {
    if(valid(str)){
        sign = str[0];
        integer = str.substr(1,str.find('.')-1);
        decimal = str.substr(str.find('.')+1);
        fullRealNumber = sign + integer + '.' + decimal;
    }
    else{
        cout<<"The number is invalid\n";
    }
}

bool BigReal::valid(std::string str) {
    if(str[0] != '+' && str[0] != '-')
        return false;
    if((str[1] > '9' || str[1] < '0') && str[1] != '.')
        return false;
    int cnt = 0;
    for(auto i : str){
        if(i == '.')
            cnt++;
    }
    return (cnt <= 1);
}

BigReal BigReal::operator + (BigReal & another) {
    BigReal ans("+.");
    if(sign == another.sign){
        int mx,mn,indic;
        if(decimal.size() >= another.decimal.size()){
            mx = decimal.size();
            mn = another.decimal.size();
            indic = 0;
        }
        else{
            mn = decimal.size();
            mx = another.decimal.size();
            indic = 1;
        }
        //decimal
        ans.decimal = (indic)? another.decimal.substr(mn): decimal.substr(mn);
        int carry = 0;
        for(int i = mn - 1  ; i >= 0 ; i-- ){
            int add = (decimal[i] - '0') + ( another.decimal[i] - '0') + carry;
            if(add > 9){
                ans.decimal = to_string(add-10) + ans.decimal;
                carry = 1;
            }
            else{
                ans.decimal = to_string(add) + ans.decimal;
                carry = 0;
            }
        }
        //int
        if(integer.size() >= another.integer.size()){
            mx = integer.size();
            mn = another.integer.size();
            indic = 0;
        }
        else{
            mn = integer.size();
            mx = another.integer.size();
            indic = 1;
        }
        for (int i = integer.size() - 1 , j = another.integer.size() - 1; (i >= 0 && j >= 0) ; --i , --j) {
            int add = (integer[i] - '0') + ( another.integer[j] - '0') + carry;
            if(add > 9){
                ans.integer = to_string(add-10) + ans.integer;
                carry = 1;
            }
            else{
                ans.integer = to_string(add) + ans.integer;
                carry = 0;
            }
        }
        ans.integer = (indic)? another.integer.substr(0,mx-mn) : integer.substr(0,mx-mn) + ans.integer;
        if(carry)
            ans.integer = '1' + ans.integer;
        ans.fullRealNumber = ans.sign + ans.integer + "." + ans.decimal;
    }
    else{

    }
    return ans;
}

//
//BigReal BigReal::operator - (BigReal &another) {
//
//}
//
//bool BigReal::operator < (BigReal &anotherReal) {
//
//}
//
//bool BigReal::operator == (BigReal &anotherReal) {
//
//}
//
//bool BigReal::operator > (BigReal &anotherReal) {
//
//}

void BigReal::print() {
    if(valid(fullRealNumber)){
        cout<< sign << integer << '.' << decimal;
    }
}

