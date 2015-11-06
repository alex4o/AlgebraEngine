#ifndef EquationHeader
#define EquationHeader

#include "Expression.hpp"
#include "RootDescriptor.hpp"
#include "SPolynomial.hpp"
#include "RNG.hpp"
#include "EquationDescriptor.hpp"

class Equation
{
public: //Всяко уравнения има два израза: лява и дясна част
    Expression left, right;
    RNJ jesus; //и генератор - това ще се промени
    RootDescriptor rd; //за момента описанието на корените служи и за описания на скобите, но това ще се промени
    CoefDescriptor cf, transformCF;
    bool nice;

    char letter; //това е променливата
    char rtype;

    vector<Number> roots; //тук се съхраняват корените
    //за момента такива винаги има, но не за дълго
    Equation()
    {

    }

    void create(EquationDescriptor &ed, RNJ& rnj)
    { //тази функции създава основата на уравнението, без никакви "украшения"
        rd=ed.rd;
        rtype=ed.type;
        SPolynomial seed; //За генерация се ползва SPolynomial, защото е по-бърз, когато
        seed.letter = letter = ed.letter; //полинома е само на 1 буква
        if(ed.type==0)
        {
            seed.coef[0]=1;
            nice = ed.nice;
            //получва се като се умножат изрази от типа (х-хi), където хi е корен
            for(int i = 0; i < ed.power; i++)
            {
                Number root = rnj.nextNumber(rd); //тук се избира корена

                roots.push_back(root);

                SPolynomial sp;
                sp.power=1;
                sp.coef[0] = root*-1; //тук се създава израза (x-xi)
                sp.coef[1] = 1;
                if(ed.nice && !root.isNatural()) //ако е nice, х+1/3 става 3х+1
                {
                    sp.coef[0]*=root.fraction.down;
                    sp.coef[1]*=root.fraction.down;
                }

                seed*=sp; //тук се случва гореспоменантото умножение
            }

            left.free = seed.toPolynomial(); //тук става превръшането от SPolynomial към Polynomial,
        }                                    //който се ползва от Expression
        else if(ed.type==1)
        {
            left.free = Polynomial(rnj.nextNumber(rd));
        }
        else if(ed.type==2)
        {
            left.free = Polynomial(Number(0));
        }
    }


    void createMod(int power, RootDescriptor& _rd, bool nice)
    { //тази функция създава модулно уравнение, все още е WIP
        rd=_rd; // и не се използва
        SPolynomial seed;
        seed.coef[0]=1;

        for(int i = 0; i < power; i++)
        {
            Number root = jesus.nextNumber(rd);
            SPolynomial sp;
            sp.power=1;
            sp.coef[0] = root;
            sp.coef[1] = 1;
            if(nice && !root.isNatural())
            {
                sp.coef[0]*=root.fraction.down;
                sp.coef[1]*=root.fraction.down;
            }

            seed*=sp;
        }

        Term t;
        t.isMod=true;
        t.polys.push_back(seed.toPolynomial());
        t.powers.push_back(1);
        t.coef=1;
        left.terms.push_back(t);

        Number num = jesus.nextNumber(rd);
        right.free = Polynomial(num);
    }

    void addTerm(int maxPow, RNJ& rnj)
    { //Добавя "скоба" към уравнението - т.е. еквиваленто преобразувание
        Term t = rnj.nextTerm(cf, maxPow, letter, nice, letter); //Засега като параметри на скбоата се ползва
        t.coef = rnj.nextNumber(transformCF);

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

    void balance()
    { //тази функция балансира броя на скоби от двете страни на знака
        int len1 = left.getLen();
        int len2 = right.getLen();

        if(len1-len2>1)
        {
            int ttm = len1 - (len1+len2)/2; //ttm = terms to move
            for(int i = 0; i < ttm; i++)
            {
                int idx = jesus.nextInt(0, left.terms.size()-1);
                Term extract = left.terms[idx];
                left.terms.erase(left.terms.begin()+idx); //спазва правилата за еквиваленто преобразувание
                extract.coef*=-1; //прехвърляме с обратен знак
                right.terms.push_back(extract);
            }
        }
        else if(len2-len1>1)
        {
            int ttm = len2 - (len1+len2)/2; //ttm = terms to move
            for(int i = 0; i < ttm; i++)
            {
                int idx = jesus.nextInt(0, right.terms.size()-1);
                Term extract = right.terms[idx];
                right.terms.erase(right.terms.begin()+idx);
                extract.coef*=-1;
                left.terms.push_back(extract);
            }
        }
        return;
    }

    void condenseFree()
    { //тази функции оставя свободен полином само от една страна на равното
        right.free.negate();
        left.free = left.free + right.free;
        right.free.clear();
    }

    void print(stringstream& ss)
    {//тази функция сама се обяснява
        left.print(ss);
        ss<<" = ";
        right.print(ss);
    }

    void printRoots(stringstream& ss)
    {//и тази
        if(rtype==2) ss<<letter<<"\\in \\R";
        else if(rtype==1) ss<<letter<<"\\in \\varnothing";
        int last = roots.size()-1;
        for(int i = 0; i < roots.size(); i++)
        {
            ss<<letter<<"_{"<<i+1<<"}=";
            roots[i].print(false, false, ss);
            if(i!=last)ss<<", ";
        }
    }
};

#endif