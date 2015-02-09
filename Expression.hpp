#ifndef ExpH
#define ExpH

#include "Polynomial.hpp"
#include "../Polynomial.hpp"

class Term
{
public:
    Polynomial p;
    Number power;
    Number coef;

    Term(Polynomial pol, Number n)
    {
        p = pol;
        power = n;
    }
};

class Expression
{
    Polynomial free;
    vector<Term> terms;

    Expression()
    {

    }

    Expression(Number n)
    {
        free = Polynomial(n);
    }

    void addTerm(Term t, bool add)
    {
        if(add)
        {
            free = free + pow(t.p, t.power);
        }
        else
        {
            terms.push_back(t);
        }
    }

    void multByNum(Number n)
    {
        free.multByMono(Monomial(n));
        for(int i = 0; i < terms.size(); i++)
        {
            terms[i].coef = terms[i].coef*n;
        }
    }
};

#endif