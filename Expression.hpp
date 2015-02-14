#ifndef ExpH
#define ExpH

#include "Polynomial.hpp"
#include <vector>

using namespace std;

class Term
{
public:
    vector<Polynomial> polys;
    vector<Number> powers;
    Number coef;

    Term()
    {

    }

    Term(Number c)
    {
        coef=c;
    }

    Term(Polynomial pol, Number n)
    {
        polys.push_back(pol);
        coef = n;
    }
};

Polynomial calc(Term& t)
{
    Polynomial result = pow(t.polys[0], t.powers[0]);
    for(int i = 1; i < t.polys.size(); i++)
    {
        result = result * pow(t.polys[i], t.powers[i]);
    }
    return result;
}

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

    void addTerm(Term& t, bool add)
    {
        if(add)
        {
            free = free + calc(t);
        }
        else
        {
            terms.push_back(t);
        }
    }

    void multByNum(Number n)
    {
        free = multByMono(free, Monomial(n));
        for(int i = 0; i < terms.size(); i++)
        {
            terms[i].coef = terms[i].coef*n;
        }
    }
};

#endif