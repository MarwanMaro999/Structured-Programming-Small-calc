#include <bits/stdc++.h>

using namespace std;

#ifndef ASS2_BIGREAL_H
#define ASS2_BIGREAL_H


class BigReal {
private:
    char sign; //+,-
    string integer, decimal;
public:
    //default contructor
    BigReal():sign('+'),integer("0"),decimal("0"){

    }
    BigReal(string str){

    }

    //operations
    BigReal operator +(BigReal& another){

    }

    BigReal operator -(BigReal& another){

    }

    BigReal operator ==(BigReal& anotherReal){

    }

    BigReal operator >=(BigReal& anotherReal){

    }

    BigReal operator <=(BigReal& anotherReal){

    }

    void print()
    {
        cout<< sign<< integer<< '.'<< decimal;
    }

};


#endif //ASS2_BIGREAL_H
