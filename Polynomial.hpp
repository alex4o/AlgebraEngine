#ifndef Polynomial_h
#define Polynomial_h

#include "Monomial.hpp"
#include <iostream>

#include <assert.h>

class Polynomial
{
public:
    int totalPower;
    std::vector<Monomial> monos;

    Polynomial(std::vector<Monomial> v) //Само се обяснява
    {                              //Важно е да има ред за да се печели скорост
        monos=v;
        std::sort(monos.begin(), monos.end(), cmpMono);
        totalPower = monos[0].totalPower;
    }

    Polynomial(std::vector<Monomial> v, int pow) //Ако вектора вече е сортиран
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

	Polynomial(char ltr, Number& root)
	{
		Monomial first, second(root);

		Simple s(ltr, 1);

		first.simples.push_back(s);
		first.totalPower = 1;
		first.coef = Number(1);

		second.coef.fraction.up *= -1;
		monos.push_back(first);
		monos.push_back(second);
	}

	int doNothingTest()
	{
		return 4;
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
			//char origSign = monos[i].getSign();
            ss<<' '<<monos[i].getSign()<<' ';
            monos[i].print(ss, true);

			//assert(origSign == monos[i].getSign());
        }
    }

    void print(stringstream& ss, bool style)
    {
		if (isZero())
		{
			ss << '0';
			return;
		}
		if (style || monos[0].getSign() == '-')
		{
			if (style)
			{
				ss << ' ' << monos[0].getSign() << ' ';
				monos[0].print(ss, true);
			}
			else monos[0].print(ss, false);
		}
		else monos[0].print(ss, false);
        
        for(int i = 1; i < monos.size(); i++)
        {
            ss<<' '<<monos[i].getSign()<<' ';
            monos[i].print(ss, true);
        }
    }

	void dbgPrint()
	{
		stringstream ss;
		print(ss);
		cout << ss.str() << endl;
	}

    bool empty()
    {
        return monos.size()==0;
    }

    void negate();
    void clear();

	bool isZero()
	{
		if (monos.size() == 0) return true;
		if (monos.size() > 1) return false;
		return monos[0].totalPower == 0 && monos[0].coef.null;
	}

	bool isOne()
	{
		if (monos.size() != 1) return false;
		return monos[0].isOne();
	}

	bool isNegative()
	{
		if (monos.empty()) return false;
		else return monos[0].getSign() == '-';
	}

	int getMaxPower()
	{
		if (monos.size() == 0) return 0;
		return monos[0].totalPower;
	}

	bool equals(Polynomial* p)
	{
		if (monos.size() != p->monos.size()) return false;
		for (int i = 0; i < monos.size(); i++)
		{
			if (!monos[i].equals(p->monos[i])) return false;
		}
		return true;
	}

    void multByNumber(Number& n);
};

Polynomial operator+(const Polynomial &p1, const Polynomial &p2);
Polynomial operator*(const Polynomial &p1, const Polynomial &p2);
Polynomial multByMono(const Polynomial &p, const Monomial &m);
Polynomial pow(Polynomial p, int num);
Polynomial pow(Polynomial p, Number num);
#endif