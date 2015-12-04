#ifndef SPoly
#define SPoly

#include "Number.hpp"
#include <iostream>


using namespace std;

#define MAXPOW 21

class SPolynomial
{ //Това е клас за полином на само една буква
public: //Не може да се използва за общи цели както Polynomial, но за сметка на това е по-бърз
    Number coef[MAXPOW]; //което го прави по-полезен за генерация на уравнения, например.
    char letter; //Съдържа масив, където i-тият елемент означава коефицента
    int power; //преди промелнивата на i-та степен

    SPolynomial()
    {
        power=0;
        letter='x'; //за удобоство по default буквата е х
        coef[0]=0;
    }

    SPolynomial(char _letter)
    {
        letter=_letter;
        power=0;
        coef[0]=0;
    }

    void normalize()
    {
        while(coef[power]==0) power--; //понякога се получава първите елемнти да са 0
    }

    SPolynomial operator+(const SPolynomial& sp)
    { //тази функция се обяснява сама
        SPolynomial n;
        int max = power;
        if(sp.power>power) max=sp.power;
        n.power=max;
        for(int i = 0; i <= power; i++) n.coef[i]+=coef[i];
        for(int i = 0; i <= sp.power; i++) n.coef[i]+=sp.coef[i];
        n.normalize();
        return n;
    }

    SPolynomial operator-(const SPolynomial& sp)
    { //аналогично на горната
        SPolynomial n;
        int max = power;
        if(sp.power>power) max=sp.power;
        n.power=max;
        for(int i = 0; i <= power; i++) n.coef[i]+=coef[i];
        for(int i = 0; i <= sp.power; i++) n.coef[i]-=sp.coef[i];
        n.normalize();
        return n;
    }

    SPolynomial operator*(const SPolynomial& sp)
    { //Функция за умножение, аналогична на тази за Polynomial
        SPolynomial result; //но по-проста и бърза
        result.power = power+sp.power;
        for(int i = 0; i <= power; i++)
        {
            for(int j = 0; j <= sp.power; j++)
            {
                result.coef[i+j]+=coef[i]*sp.coef[j];
            }
        }
        return result;
    }

    void operator*=(const SPolynomial& sp)
    { //аналогично на горната, но самият SPolynomial се умножава
        Number oldCoef[MAXPOW];
        int oldPower=power;
        for(int i = 0; i <= oldPower; i++)
        {
            oldCoef[i]=coef[i];
        }

        power+=sp.power;
        for(int i = 0; i <= power; i++) coef[i]=0;

        for(int i = 0; i <= oldPower; i++)
        {
            for(int j = 0; j <=sp.power; j++)
            {
                coef[i+j]+=oldCoef[i]*sp.coef[j];
            }
        }
    }

    void print(stringstream& ss)
    { //ползва се за debug
        for(int i = 0; i <= power; i++)
        {
            coef[i].print(false, false, ss);
            ss<<' ';
        }
    }

    Polynomial toPolynomial()
    { //Прави трансформацията от SPolynomial към Polynomial
        Polynomial result;

        for(int i = power; i > 0; i--)
        {
            if(coef[i]==0) continue;
            result.monos.push_back(Monomial(coef[i], letter, i));
            result.totalPower=power;
        }
        if(coef[0]!=0)result.monos.push_back(Monomial(coef[0]));
        return result;
    }
};

#endif