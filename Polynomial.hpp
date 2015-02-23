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

    Polynomial(Number n)
    {
        totalPower=0;
        monos.push_back(Monomial(n));
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

    void print(stringstream& ss)
    {
        monos[0].print(ss, false);
        for(int i = 1; i < monos.size(); i++)
        {
            ss<<' '<<monos[i].getSign()<<' ';
            monos[i].print(ss, true);
        }
    }

    void print(stringstream& ss, bool style)
    {
        ss<<' '<<monos[0].getSign()<<' ';
        monos[0].print(ss, true);
        for(int i = 1; i < monos.size(); i++)
        {
            ss<<' '<<monos[i].getSign()<<' ';
            monos[i].print(ss, true);
        }
    }

    bool empty()
    {
        return monos.size()==0;
    }

    void negate();
    void clear();
};

Polynomial operator+(const Polynomial &p1, const Polynomial &p2);
Polynomial operator*(const Polynomial &p1, const Polynomial &p2);
Polynomial multByMono(const Polynomial &p, const Monomial &m);
Polynomial pow(Polynomial p, int num);
Polynomial pow(Polynomial p, Number num);
#endif