#ifndef Monomial_h
#define Monomial_h

#include "Simple.hpp"
#include "Number.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
class Monomial //Клас за сложен едночлен, от типа х2у3
{
public:

    int totalPower; //Степента на едночлена
    std::vector<Simple> simples; //Логично е сложния едночлен да е сбор от прости
    Number coef; //Коефицента пред едночлена

    void sortSimple();

    Monomial();

    Monomial(Number n);

    Monomial(std::string s, int* idx);

    Monomial(Number c, std::vector<Simple> v);

    Monomial(Number c, char letter);

    void print(stringstream& ss, bool ignoreSign)
    {
        coef.print(totalPower!=0, ignoreSign, ss);
        for(int i = 0; i < simples.size(); i++)
        {
            if(simples[i].pow==1) ss<<simples[i].letter;
            else ss<<simples[i].letter<<"^"<<simples[i].pow;
        }
    }

    char getSign()
    {
        if(coef.fraction.up<0) return '-';
        return '+';
    }
};

Monomial operator*(const Monomial &m1, const Monomial &m2);
bool operator<(const Monomial &m1, const Monomial &m2);
bool operator>(const Monomial &m1, const Monomial &m2);
bool operator==(const Monomial &m1, const Monomial &m2);


bool cmpMono(Monomial m1, Monomial m2);
#endif
