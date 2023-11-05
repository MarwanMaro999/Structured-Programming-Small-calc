#include <bits/stdc++.h>

using namespace std;

#ifndef A2_OOP_BigReal_H
#define A2_OOP_BigReal_H


class BigReal {
private:
    char sign; //+,-
    string integer, decimal;
    string fullRealNumber;
    //operations
    bool valid(string str);
    void leading_zeros();

public:
    //default constructor
    BigReal();
    //constructor overloading
    BigReal(string str);
    //operator overloading
    char get_sign();
    int get_size();
    BigReal& operator= (string str);
    BigReal operator + (BigReal& another);
    BigReal operator - (BigReal& another);
    bool operator == (BigReal& anotherReal);
    bool operator > (BigReal& anotherReal);
    bool operator < (BigReal& anotherReal);
    friend ostream& operator << (ostream& ccout,BigReal& BR);
    void print();

};

#endif //A2_OOP_BigReal_H
