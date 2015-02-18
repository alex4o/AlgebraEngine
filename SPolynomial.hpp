#ifndef SPoly
#define SPoly

#include "Number.hpp"
#include <iostream>


using namespace std;

#define MAXPOW 21

class SPolynomial
{
public:
    Number coef[MAXPOW];
    char letter;
    int power;

    void normalize()
    {
        while(coef[power]==0) power--;
    }

    /*void print()
    {
        for(int i = power; i>=0; i--)
        {
            if(coef[i]==0) continue;
            coef[i].print();
            cout<<letter<<"^"<<i<<" + ";
        }
    }*/

    SPolynomial operator+(const SPolynomial& sp)
    {
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
    {
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
    {
        SPolynomial result;
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
};

#endif