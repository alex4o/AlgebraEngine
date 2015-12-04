#ifndef Number_h
#define Number_h

#include "Fraction.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#define natural 0x1
#define rational 0x2

using namespace std;

int gcd ( int a, int b );

class Number          //Класа за "математическо число"
{                     //В момента поддържа само рационални числа, но в бъдеще ще поддържа и ирационлани
public:

    bool null; //ако числото е 0. Оптимизации
    char type; //Побитово пазим типа на числото - първия бит показва дали е естсетвено, а втория - дали е рационнално
    Fraction fraction; //Дробта, която представлява числото - ако е естествено, знаменателя е 1

    Number();

    Number(int n);

    Number(int _up, int _down);

    bool isNatural() const     //Тези 2 функции се обясняват сами
    {
        return fraction.down==1;
    }

    bool isRational() const
    {
        return type&rational;
    }

    void operator+=(const Number &n1);
    void operator-=(const Number &n1);

    bool operator==(int k)
    {
        if(k==0) return fraction.up==0;
        if(isNatural()) return fraction.up==k;
        return false;
    }

    bool operator==(const Number& n1)
    {
        if(null && n1.null) return true;
        return type==n1.type && fraction.up==n1.fraction.up && fraction.down==n1.fraction.down;
    }

    bool operator!=(int k)
    {
        if(k==0) return fraction.up!=0;
        if(isNatural()) return fraction.up!=k;
        return true;
    }

    void operator=(int k)
    {
        fraction.up=k;
        fraction.down=1;
        type=natural| rational;
        if(k) null=false;
    }

    void operator*=(int k)
    {
        fraction.up*=k;
        int g = gcd(fraction.up, fraction.down);
        if(g==1) return;
        fraction.up/=g;
        fraction.down/=g;
        if(fraction.down==1) type = rational | natural;
    }

    void operator*=(const Number& n)
    {

        fraction.up*=n.fraction.up;
        fraction.down*=n.fraction.down;
        int g = gcd(fraction.up, fraction.down);
        if(g!=1)
        {
            fraction.up /= g;
            fraction.down /= g;
        }

        if(fraction.down==1) type = rational | natural;
        else type = rational;
        if(fraction.up==0) null=true;

    }

    void print(bool ignoreOne, bool ignoreSign, stringstream& ss);

    char getSign()
    {
        if(fraction.up<0) return '-';
        return '+';
    }

	bool equals(Number& n)
	{
		if (type != n.type) return false;
		return fraction.up == n.fraction.up && fraction.down == n.fraction.down;
	}

	void flipSign()
	{
		fraction.up *= -1;
	}

	bool operator<(const Number& n) const
	{
		int top = fraction.up*n.fraction.down - n.fraction.up*fraction.down;
		int bottom = fraction.down*n.fraction.down;
		return (top ^ bottom)&(1<<31);
	}
};

Number operator+(const Number &n1, const Number &n2);
Number operator-(const Number &n1, const Number &n2);
Number operator*(const Number &n1, const Number &n2);
Number operator/(const Number &n1, const Number &n2);

static bool cmpNum(Number* n1, Number* n2)
{
    if(n1==0 || n2==0) return false;
	return (*n1) < (*n2);
}

Number parseNum(std::string s);
#endif