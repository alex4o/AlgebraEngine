//
// Created by Kosyo on 27.4.2015 г..
//

#ifndef ALGEBRAENGINE_INEQUATION_HPP
#define ALGEBRAENGINE_INEQUATION_HPP

#include "Expression.hpp"
#include "InequationDescriptor.hpp"
#include "Interval.hpp"
#include "RNG.hpp"
#include <string>


class Inequation
{
private:
    string lookup[4] = {">", "\\geq", "\\leq", "<"};

public:
    Expression left, right;
    char sign; //0 - >, 1 - >=, 2 - <=, 3 - <
    Interval solution;
    char letter;
    bool nice;
    CoefDescriptor cf, trCf;

    RNJ rnj;

    void create(InequationDescriptor& id)
    {
        letter = id.letter;

        Number root = rnj.nextNumber(id.rd);
        sign = rnj.nextInt(0, 3);

        solution = Interval(root, sign);

        nice = id.nice;
        cf = id.cf;
        trCf = id.transformCF;

        if(id.nice)
        {
            left = Expression(Number(root.fraction.down), letter);
            right = Expression(Number(root.fraction.up));
        }
        else
        {
            left = Expression(Number(1), letter);
            right = Expression(root);
        }

    }

    void addTerm(int power)
    {
        Term t = rnj.nextTerm(cf, power, letter, nice, letter);
        t.coef = rnj.nextNumber(trCf);

        if(rnj.nextBool()) //описанието на корените, но това ще се промени
        {
            left.addTerm(t, false); //винаги скобата се добавя към едната страна "сурова",
            right.addTerm(t, true); //а към другата разкрита
        }
        else
        {
            left.addTerm(t, true);
            right.addTerm(t, false);
        }
    }

    void invertSign()
    {
        sign = 3 - sign;
    }

    void addNumber()
    {
        Number num = rnj.nextNumber(cf);
        if(num.fraction.up<0) invertSign();

        right.multByNum(num);
    }

    void multiplyByNumber()
    {
        Number num = rnj.nextNumber(trCf);
        if(num.fraction.up<0) invertSign();
        left.multByNum(num);
        right.multByNum(num);
    }

    void print(stringstream& ss)
    {
        left.print(ss);
        ss<<" "<<this->lookup[sign]<<" ";
        right.print(ss);
    }

    void printRoots(stringstream& ss)
    {
        solution.print(ss);
    }

};

#endif //ALGEBRAENGINE_INEQUATION_HPP
