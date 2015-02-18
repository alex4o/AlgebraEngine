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

    Polynomial toPoly()
    {
        Polynomial result = pow(polys[0], powers[0]);
        for(int i = 1; i < polys.size(); i++)
        {
            result = result * pow(polys[i], powers[i]);
        }
        result = multByMono(result, Monomial(coef));
        return result;
    }
};

class Expression
{
public:
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
            free = free + t.toPoly();
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

    void print(stringstream& ss)
    {
        if(terms.size()>0)
        {
            terms[0].coef.print(true, false, ss);
            for(int j = 0; j < terms[0].polys.size(); j++)
            {
                ss<<"(";
                terms[0].polys[j].print(ss);
                ss<<")";

                if(terms[0].powers[j]!=1)
                {
                    ss<<"^";
                    terms[0].powers[j].print(true, false, ss);
                }

            }

            for(int i = 1; i < terms.size(); i++)
            {
                ss<<' '<<terms[i].coef.getSign()<<' ';

                terms[i].coef.print(true, true, ss);
                for(int j = 0; j < terms[i].polys.size(); j++)
                {
                    ss<<"(";
                    terms[i].polys[j].print(ss);
                    ss<<")";

                    if(terms[i].powers[j]!=1)
                    {
                        ss<<"^";
                        terms[i].powers[j].print(true, false, ss);
                    }

                }
            }
        }

        if(!free.empty())
        {
            if(terms.empty()) free.print(ss);
            else free.print(ss, true);
        }
    }
};

#endif