#ifndef EquationHeader
#define EquationHeader

#include "Expression.hpp"
#include "RootDescriptor.hpp"
#include "SPolynomial.hpp"
#include "RNG.hpp"
#include "EquationDescriptor.hpp"

class Equation
{
public:
    Expression left, right;
    RNJ jesus;
    RootDescriptor rd;
    CoefDescriptor cf, transformCF;
    bool nice;

    char letter;
    char rtype;

    vector<Number> roots;

    Equation()
    {

    }

    void create(EquationDescriptor &ed, RNJ& rnj)
    {
        rd=ed.rd;
        rtype=ed.type;
        SPolynomial seed;
        seed.letter = letter = ed.letter;

        cf=ed.cd;
        transformCF = ed.transformCF;
        if(ed.type==0)
        {
            seed.coef[0]=1;
            nice = ed.nice;

            for(int i = 0; i < ed.power; i++)
            {
                Number root = rnj.nextNumber(rd);

                roots.push_back(root);

                SPolynomial sp;
                sp.power=1;
                sp.coef[0] = root*-1;
                sp.coef[1] = 1;
                if(ed.nice && !root.isNatural()) //ако е nice, х+1/3 става 3х+1
                {
                    sp.coef[0]*=root.fraction.down;
                    sp.coef[1]*=root.fraction.down;
                }

                seed*=sp;
            }

            left.free = seed.toPolynomial();
        }
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
    { // не работи
        rd=_rd; 
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
    {
        Term t = rnj.nextTerm(cf, maxPow, letter, nice, letter);
        t.coef = rnj.nextNumber(transformCF);

        if(rnj.nextBool())
        {
            left.addTerm(t, false);
            right.addTerm(t, true);
        }
        else
        {
            left.addTerm(t, true);
            right.addTerm(t, false);
        }
    }

    void balance()
    { 
        int len1 = left.getLen();
        int len2 = right.getLen();

        if(len1-len2>1)
        {
            int ttm = len1 - (len1+len2)/2; //ttm = terms to move
            for(int i = 0; i < ttm; i++)
            {
                int idx = jesus.nextInt(0, left.terms.size()-1);
                Term extract = left.terms[idx];
                left.terms.erase(left.terms.begin()+idx); 
                extract.coef*=-1; 
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
    {
        right.free.negate();
        left.free = left.free + right.free;
        right.free.clear();
    }

    void print(stringstream& ss)
    {
        left.print(ss);
        ss<<" = ";
        right.print(ss);
    }

    void printRoots(stringstream& ss)
    {
        if(rtype==2) ss<<letter<<"\\in R";
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