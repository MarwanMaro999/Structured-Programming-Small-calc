#include "BigReal.h"

#include <bits/stdc++.h>

using namespace std;

BigReal::BigReal():sign('+') , integer("") , decimal(""),fullRealNumber("+."){
}

BigReal::BigReal(string str) {
    if(valid(str)){
        sign = (str[0] == '+' || str[0] == '-')? sign = str[0] : sign = '+';
        (str[0] == '+' || str[0] == '-')? str = "" + str : str = sign + str;
        if(str.find('.') != str.npos){
            integer = str.substr(1,str.find('.')-1);
            decimal = str.substr(str.find('.')+1);
        }
        else{
            integer = str.substr(1);
            decimal = "0";
        }
        fullRealNumber = sign + integer + '.' + decimal;
        leading_zeros();
    }
    else{
        cout<<"The number is invalid\n";
    }
}

BigReal &BigReal::operator=(std::string str) {
    if(valid(str)){
        sign = (str[0] == '+' || str[0] == '-')? sign = str[0] : sign = '+';
        (str[0] == '+' || str[0] == '-')? str = "" + str : str = sign + str;
        if(str.find('.') != str.npos){
            integer = str.substr(1,str.find('.')-1);
            decimal = str.substr(str.find('.')+1);
        }
        else{
            integer = str.substr(1);
            decimal = "0";
        }
        fullRealNumber = sign + integer + '.' + decimal;
        leading_zeros();
    }
}

char BigReal::get_sign() {
    return sign;
}

int BigReal::get_size() {
    return fullRealNumber.size()-2;
}

void BigReal::leading_zeros() {
    while(integer.front() == '0'){
        integer.erase(integer.begin());
    }
    while(decimal.back() == '0'){
        decimal.erase(decimal.end()-1);
    }
    if(decimal.empty())
        decimal = "0";
    if(integer.empty())
        integer = "0";
    fullRealNumber = sign + integer + "." + decimal;
}

bool BigReal::valid(string str) {
    int Ndots = 0 , Nsigns = 0 , N_non_digits = 0;
    for(auto i : str){
        if(i == '.')
            Ndots++;
        else if(i == '+' || i == '-')
            Nsigns++;
        else if(i < '0' || i > '9')
            N_non_digits++;
    }
    return (Ndots <= 1 && Nsigns <= 1 && !N_non_digits);
}

BigReal BigReal::operator + (BigReal & another) {
    BigReal ans;
    if(sign == another.sign){
        if(sign == '+')
            ans.sign = '+';
        else
            ans.sign = '-';
        //decimal
        int mn,indic;
        if(decimal.size() >= another.decimal.size()){
            mn = another.decimal.size();
            indic = 0;
        }
        else{
            mn = decimal.size();
            indic = 1;
        }
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
        //integer
        int diff;
        if(integer.size() >= another.integer.size()){
            diff = integer.length() - another.integer.length();
            for (int i = 0; i < diff; ++i) {
                another.integer = "0" + another.integer;
            }
        }
        else{
            diff = another.integer.length() - integer.length();
            for (int i = 0; i < diff; ++i) {
                integer = "0" + integer;
            }
        }
        for (int i = integer.size() - 1  ; i >= 0  ; --i ) {
            int add = (integer[i] - '0') + ( another.integer[i] - '0') + carry;
            if(add > 9){
                ans.integer = to_string(add-10) + ans.integer;
                carry = 1;
            }
            else{
                ans.integer = to_string(add) + ans.integer;
                carry = 0;
            }
        }
        if(carry)
            ans.integer = '1' + ans.integer;
        ans.fullRealNumber = ans.sign + ans.integer + "." + ans.decimal;
    }
    else{
        BigReal copy;
        if(sign == '-'){
            copy = *this;
            copy.sign = '+';
            ans = another - copy;
        }
        else{
            copy = another;
            copy.sign = '+';
            ans = *this - copy;
        }
    }
    leading_zeros();
    return ans;
}

BigReal BigReal::operator - (BigReal &another) {
    BigReal ans;
    if(sign == another.sign){ // -rkm - -rkm | rkm - rkm
        BigReal this_copy = *this,another_copy = another;
        this_copy.sign = '+',another_copy.sign = '+';
        if(this_copy > another_copy || this_copy == another_copy){ //9 - 9 | -9 - -10
            this_copy = *this;
            another_copy = another;
        }
        else{ //9 - 10 | -9 - -8
            another_copy = *this;
            this_copy = another;
        }
        if(*this > another || *this == another)
            ans.sign = '+';
        else
            ans.sign = '-';
        //decimal
        while(this_copy.decimal.size() > another_copy.decimal.size())
            another_copy.decimal.push_back('0');
        while(this_copy.decimal.size() < another_copy.decimal.size())
            this_copy.decimal.push_back('0');
        int handle;
        for (int i = this_copy.decimal.size()-1; i >= 0 ; --i) {
            //.01234
            //.10008
            //.09877
            //=
            //.00131
            if(this_copy.decimal[i] >= another_copy.decimal[i]){
                ans.decimal = to_string(this_copy.decimal[i]-another_copy.decimal[i]) + ans.decimal;
            }
            else{
                int idx = i-1;
                while(idx >= 0 && this_copy.decimal[idx] == '0'){
                    this_copy.decimal[idx] = '9';
                    idx--;
                }
                if(idx != -1)
                    this_copy.decimal[idx]--;
                else
                    handle = 1;
                int d1 = (this_copy.decimal[i] - '0') + 10 , d2 = another_copy.decimal[i] - '0';
                ans.decimal = to_string(d1-d2) + ans.decimal;
            }
        }

        //integer
        while (this_copy.integer.size() > another_copy.integer.size()){
            another_copy.integer = '0' + another_copy.integer;
        }
        // 01234
        // 10500.10008
        // 09377.09877
        int idx = this_copy.integer.size() - 1;
        if (handle){
            while(idx >= 0 && this_copy.integer[idx] == '0'){
                this_copy.integer[idx] = '9';
                idx--;
            }
            this_copy.integer[idx]--;
        }
        for (int i = this_copy.integer.size()-1; i >= 0 ; --i) {
            if(this_copy.integer[i] >= another_copy.integer[i]){
                ans.integer = to_string(this_copy.integer[i]-another_copy.integer[i]) + ans.integer;
            } else{
                idx = i-1;
                while(idx >= 0 && this_copy.integer[idx] == '0'){
                    this_copy.integer[idx] = '9';
                    idx--;
                }
                this_copy.integer[idx]--;
                int int1 = (this_copy.integer[i] - '0') + 10 , int2 = another_copy.integer[i] - '0';
                ans.integer = to_string(int1-int2) + ans.integer;
            }
        }
    }
    else{ // 9 - -10 | 10 - -9 | -10 - 9 | -9 - 10
        BigReal another_copy = another;
        another_copy.sign = (another.sign == '+')? '-' : '+';
        ans = *this + another_copy;
    }
    leading_zeros();
    return ans;
}

bool BigReal::operator < (BigReal &anotherReal) {
    if(sign=='-' && anotherReal.sign == '+'){
        return true;
    }else if (sign=='+' && anotherReal.sign == '-'){
        return false;
    }else if (sign=='-' && anotherReal.sign == '-'){
        if(integer.size() < anotherReal.integer.size()){
            return false;
        }else if (integer.size() > anotherReal.integer.size()){
            return true;
        }else {
            bool v = true;
            for (int i = 0, j = 0; i < integer.size(); ++i) {
                if (integer[i] < anotherReal.integer[i]) {
                    v = false;
                    return false;
                    break;
                } else if (integer[i] > anotherReal.integer[i]) {
                    v = false;
                    return true;
                    break;
                }
            }
            if (v) {
                bool b = true;
                int mn = min(decimal.size(), anotherReal.decimal.size());
                for (int i = 0, j = 0; i < mn; ++i) {
                    if (decimal[i] < anotherReal.decimal[i]) {
                        v = false;
                        return false;
                        break;
                    } else if (decimal[i] > anotherReal.decimal[i]) {
                        v = false;
                        return true;
                        break;
                    }
                }//-0.12 -0.123
                if (b) {
                    if (decimal.size() < anotherReal.decimal.size()) {
                        return false;
                    } else if (decimal.size() > anotherReal.decimal.size()) {
                        return true;
                    }else {
                        return false;
                    }
                }
            }
        }
    }else{
        if(integer.size() < anotherReal.integer.size()){
            return true;
        }else if (integer.size() > anotherReal.integer.size()){
            return false;
        }else{
            bool v = true;
            for (int i = 0,j = 0 ; i < integer.size() ; ++i) {
                if(integer[i] < anotherReal.integer[i]){
                    v= false;
                    return true;
                    break;
                }else if (integer[i] > anotherReal.integer[i]){
                    v= false;
                    return false;
                    break;
                }
            }
            if(v){
                bool b= true;
                int mn=min(decimal.size(), anotherReal.decimal.size());
                for (int i = 0 , j = 0; i <mn ; ++i) {
                    if(decimal[i] < anotherReal.decimal[i]){
                        v= false;
                        return true;
                        break;
                    }else if (decimal[i] > anotherReal.decimal[i]){
                        v= false;
                        return false;
                        break;
                    }
                }
                if(b){
                    if(decimal.size() < anotherReal.decimal.size()){
                        return true;
                    }else
                        return false;
                    }
                }
            }
        }
    }

bool BigReal::operator == (BigReal &anotherReal) {
    if(integer == anotherReal.integer && decimal == anotherReal.decimal && sign == anotherReal.sign)
        return true;
    else
        return false;
}

bool BigReal::operator > (BigReal &anotherReal) {
    if (sign == '+' and anotherReal.sign == '-')
        return true;
    else if (sign == '-' and anotherReal.sign == '+')
        return false;
    else if (sign == '+' and anotherReal.sign == '+'){
        if (integer.size() > anotherReal.integer.size())
            return true;
        else if (integer.size() < anotherReal.integer.size())
            return false;
        else {
            // the integer parts are equal in sizes ,so we will compare digit by digit 2123 1113
            bool check = true;
            for (int i = 0; i < integer.size(); ++i) {
                int int1 = integer[i]-'0';
                int int2 = anotherReal.integer[i]-'0';
                if (int1 > int2){
                    check = false;
                    return true;
                    break;
                }else if (int1 < int2){
                    check = false;
                    return false;
                }
            }
            if (check){
                for (int i = 0,j = 0; (i < decimal.size() and j < anotherReal.decimal.size()) ; ++i,j++) {
                    int d1 = decimal[i]-'0';
                    int d2 = anotherReal.decimal[j]-'0';
                    if (d1 > d2){
                        check = false;
                        return true;
                        break;
                    }else if (d1 < d2){
                        check = false;
                        return false;
                        break;
                    }
                }
                if (check){
                    //in the common digits they are equal 0.123 0,12345
                    //,so we will compare the sizes
                    if (decimal.size() > anotherReal.decimal.size())
                        return true;
                    else
                        return false; // if equal in size, or another.decimal.size is greater, both will return false
                    //we can use this to check equality
                    // decimal = another.decimal and integer = another.integer --> BigReal == anotherBigReal
                }
            }
        }
    }else{
        //-123.5 -123.56
        bool check = true;
        for (int i = 0; i < integer.size(); ++i) {
            int int1 = integer[i]-'0';
            int int2 = anotherReal.integer[i]-'0';
            if (int1 > int2){
                check = false;
                return false;
                break;
            }else if (int1 < int2){
                check = false;
                return true;
                break;
            }
        }
        //integer = another.integer
        //check decimal
        if (check){
            for (int i = 0,j = 0; (i < decimal.size() and j < anotherReal.decimal.size()) ; ++i,j++) {
                int d1 = decimal[i]-'0';
                int d2 = anotherReal.decimal[j]-'0';
                if (d1 > d2){
                    check = false;
                    return false;
                    break;
                }else if (d1 < d2){
                    check = false;
                    return true;
                    break;
                }
            }
            if (check){
                //in the common digits they are equal -0.123 -0,12345
                //,so we will compare the sizes
                if (decimal.size() > anotherReal.decimal.size())
                    return false;
                else if (decimal.size() < anotherReal.decimal.size())
                    return true;
                else
                    return false;

            }
        }
    }
}

ostream& operator<<(ostream& ccout, BigReal& BR){
    BR.leading_zeros();
    ccout << BR.sign << BR.integer << '.' << BR.decimal;
    return ccout;
}

void BigReal::print() {
    if(valid(fullRealNumber)){
        leading_zeros();
        cout<< sign << integer << '.' << decimal;
    }
}
