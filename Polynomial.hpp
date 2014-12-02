#ifndef Polynomial_h
#define Polynomial_h

#include "Monomial.hpp"
#include <iostream>



class Polynomial
{
public:
    int totalPower;
    std::vector<Monomial> monos;

    Polynomial(std::vector<Monomial> v) //Само се обяснява
    {                              //Ще има ред защото... е добре
        monos=v;
        std::sort(monos.begin(), monos.end(), cmpMono);
        totalPower = monos[0].totalPower;
    }

    Polynomial(std::vector<Monomial> v, int pow) //Ако вече е готов
    {
        monos=v;
        totalPower=pow;
    }

    Polynomial() //За общи цели
    {
        totalPower=0;
    }

    Polynomial(std::string s)
    {
        int idx = 0;

        bool sign=true; //true e +, false e -

        while(idx<s.size())
        {
            char c = s[idx];
            if(c==' ')
            {
                idx++;
                continue;
            }
            if(c=='+')
            {
                idx++;
                sign=true;
                continue;
            }
            if(c=='-')
            {
                idx++;
                sign=false;
                continue;
            }

            Monomial m(s, &idx);
            if(!sign) m.coef.fraction.up*=-1;
            monos.push_back(m);
        }

        sort(monos.begin(), monos.end(), cmpMono);
    }

    void print() const
    {
        for(int i = 0; i < monos.size(); i++)
        {
            monos[i].print();
            if(i!=monos.size()-1) std::cout<<" + ";
        }
    }
};

Polynomial operator+(const Polynomial &p1, const Polynomial &p2);
Polynomial operator*(const Polynomial &p1, const Polynomial &p2);
Polynomial multByMono(const Polynomial &p, const Monomial &m);
#endif