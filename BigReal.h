#include <bits/stdc++.h>

using namespace std;

#ifndef ASS2_BIGREAL_H
#define ASS2_BIGREAL_H


class BigReal {
private:
    char sign; // +,-
    string integer, decimal;
    string fullRealNumber;
    //operations
    bool valid(string str);
public:
    //default constructor
    BigReal();
    BigReal(string str);

    BigReal operator + (BigReal & another);

//    BigReal operator - (BigReal & another);
//
//    bool operator == (BigReal & anotherReal);
//
//    bool operator > (BigReal & anotherReal);
//
//    bool operator < (BigReal & anotherReal);

    void print();

};

#endif //ASS2_BIGREAL_H
