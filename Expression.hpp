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

    bool isMod;

    Term()
    {
        isMod=false;
    }

    Term(Number c)
    {
        coef=c;
        isMod=false;
    }

    Term(Polynomial pol, Number n)
    {
        polys.push_back(pol);
        coef = n;
        isMod=false;
    }

    Polynomial toPoly()
    {
        if(polys.empty()) return Polynomial(coef);
        Polynomial result = pow(polys[0], powers[0]);
        for(int i = 1; i < polys.size(); i++)
        {
            result = result * pow(polys[i], powers[i]);
        }

        result.multByNumber(coef);
        return result;
    }

    void print()
    {
        stringstream ss;
        coef.print(false, false, ss);
        cout<<ss.str();
        ss.str("");
        for(int i = 0; i < polys.size(); i++)
        {
            cout<<"(";
            polys[i].print(ss);
            cout<<ss.str()<<")^"<<powers[i].fraction.up;
        }
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
            cout<<"\t term: ";
            t.print();

            Polynomial tmp = t.toPoly();

            stringstream ss;
            tmp.print(ss);
            cout<<"\n\ttoPoly of term: "<<ss.str()<<endl;
            cout<<endl;

            free = free + tmp;
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
            if(terms[0].isMod) ss<<'|';

            bool skip = terms[0].isMod and terms[0].polys.size()==1;

            for(int j = 0; j < terms[0].polys.size(); j++)
            {
                if(!skip)ss<<"(";
                terms[0].polys[j].print(ss);
                if(!skip)ss<<")";

                if(terms[0].powers[j]!=1)
                {
                    ss<<"^";
                    terms[0].powers[j].print(true, false, ss);
                }

            }
            if(terms[0].isMod) ss<<'|';

            for(int i = 1; i < terms.size(); i++)
            {
                ss<<' '<<terms[i].coef.getSign()<<' ';

                terms[i].coef.print(true, true, ss);
                if(terms[i].isMod) ss<<'|';

                bool skip = terms[i].isMod and terms[i].polys.size()==1;

                for(int j = 0; j < terms[i].polys.size(); j++)
                {
                    if(!skip)ss<<"(";
                    terms[i].polys[j].print(ss);
                    if(!skip)ss<<")";

                    if(terms[i].powers[j]!=1)
                    {
                        ss<<"^";
                        terms[i].powers[j].print(true, false, ss);
                    }

                }
                if(terms[i].isMod) ss<<'|';
            }
        }

        if(!free.empty())
        {
            if(terms.empty()) free.print(ss);
            else free.print(ss, true);
        }

        if(terms.empty() and free.empty()) ss<<'0';
    }

    int getLen()
    {
        return terms.size() + (free.empty()==false);
    }
};

#endif