#ifndef EquationHeader
#define EquationHeader

#include "Expression.hpp"
#include "RootDescriptor.hpp"
#include "SPolynomial.hpp"
#include "RNG.hpp"

class Equation
{
public:
    Expression left, right;
    RNJ jesus;
    RootDescriptor rd;

    void create(int power, RootDescriptor& _rd, bool nice)
    {
        rd=_rd;
        SPolynomial seed;
        seed.coef[0]=1;

        /*stringstream ss;
        seed.print(ss);
        cout<<ss.str()<<endl;*/

        for(int i = 0; i < power; i++)
        {
            Number root = jesus.nextNumber(rd);
            SPolynomial sp;
            sp.power=1;
            sp.coef[0] = root;
            sp.coef[1] = 1;
            if(nice and !root.isNatural())
            {
                sp.coef[0]*=root.fraction.down;
                sp.coef[1]*=root.fraction.down;
            }

            seed*=sp;
            /*stringstream ss;
            sp.print(ss);
            cout<<ss.str()<<endl;*/
        }

        left.free = seed.toPolynomial();
    }

    void addTerm(int maxPow, bool nice)
    {
        Term t = jesus.nextTerm(rd, maxPow, 'x', nice);
        if(jesus.nextBool())
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

        //cout<<"Left and right: "<<len1<<" "<<len2<<endl;

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
};

#endif