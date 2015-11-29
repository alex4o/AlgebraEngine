#ifndef ALGEBRAENGINE_INTERVAL_HPP
#define ALGEBRAENGINE_INTERVAL_HPP

#include "Number.hpp"
#include "InequationDescriptor.hpp"

class Interval
{
public:
    Number left, right;
    bool negInf, posInf;
    char type; //първи бит задава лявата скоба, втория - дясната; 0 - ), 1 - ]

    Interval(Number& _left, Number& _right, bool leftClosed, bool rightClosed)
    {
        left=_left;
        right=_right;
        type=leftClosed + rightClosed*2;
    }

    Interval(Number& num, char inf_pos, bool closed)
    {
        if(inf_pos==0) // (num, +inf)
        {
            left = num;
            posInf = true;
			negInf = false;
            type=closed;
        }
        else // (-inf, num)
        {
            right = num;
            negInf = true;
			posInf = false;
            type=closed*2;
        }
    }

    Interval()
    {
        negInf = posInf = true;
        type=0;
    }

    Interval(Number& root, char sign)
    {
        if(sign==0)
        {
            left=root;
            posInf=true;
            negInf=false;
            type=0;
        }
        else if(sign==1)
        {
            left=root;
            posInf=true;
            negInf=false;
            type=1;
        }
        else if(sign==2)
        {
            right=root;
            posInf=false;
            negInf=true;
            type=2;
        }
        else if(sign==3)
        {
            right=root;
            posInf=false;
            negInf=true;
            type=0;
        }
    }

    void print(stringstream& ss)
    {
        if(type&1) ss<<'[';
        else ss<<'(';

        if(negInf) ss<<"-\\infty; ";
        else left.print(false, false, ss);
        if(posInf) ss<<"; +\\infty";
        else right.print(false, false, ss);

        if(type&2) ss<<']';
        else ss<<')';
    }
};

#endif //ALGEBRAENGINE_INTERVAL_HPP
