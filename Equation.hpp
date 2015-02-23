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
        if(left.getLen()<right.getLen())
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

    void print(stringstream& ss)
    {
        left.print(ss);
        ss<<" = ";
        right.print(ss);
    }
};

#endif