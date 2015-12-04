#include "Polynomial.hpp"
#include "Debug.hpp"

using namespace std;

Polynomial operator+(const Polynomial &p1, const Polynomial &p2) {
    int pow = 0;
    std::vector<Monomial> v;

    int lim1 = p1.monos.size();
    int lim2 = p2.monos.size();
    int idx1 = 0, idx2 = 0;


    while (idx1 < lim1 && idx2 < lim2) {
        if(p1.monos[idx1]==p2.monos[idx2]) //бързо сливане на 2 сортирани
        {                                  //масива
            Number nc = p1.monos[idx1].coef + p2.monos[idx2].coef; //При коефициент 0 просто махаме
                                                                   
            if(nc.null==false)
            {
                Monomial c(nc, p1.monos[idx1].simples);
                v.push_back(c);
            }
            idx1++;
            idx2++;
        }
        else if(p1.monos[idx1]>p2.monos[idx2])
        {
            v.push_back(p1.monos[idx1]);
            idx1++;
        }
        else
        {
            v.push_back(p2.monos[idx2]);
            idx2++;
        }
    }
    while(idx1<lim1) v.push_back(p1.monos[idx1++]);
    while(idx2<lim2) v.push_back(p2.monos[idx2++]);

    if(v.size() > 0) return Polynomial(v, v[0].totalPower);
	return Polynomial();
}

Polynomial multByMono(const Polynomial &p, const Monomial &m)
{
    std::vector<Monomial> v;
    for(int i = 0 ; i < p.monos.size(); i++)
    {
        v.push_back(p.monos[i]*m);
    }

    return Polynomial(v);
}

Polynomial operator*(const Polynomial &p1, const Polynomial &p2)
{
    Polynomial result = multByMono(p1, p2.monos[0]);

    for(int i = 1; i < p2.monos.size(); i++)
    {
        result = result+multByMono(p1, p2.monos[i]);
    }

    return result;
}

Polynomial pow(Polynomial p, int num)
{
    Polynomial result(Number(1));
    Polynomial tmp = p;

    int idx = 1;
    while(idx<=num)
    {
        if(num&idx)  result = result*tmp;
        idx<<=1;
        tmp = tmp*tmp;
    }
    return result;
}

Polynomial pow(Polynomial p, Number num)
{
    if(num.isNatural()) return pow(p, num.fraction.up);
    else return Polynomial();
}

void Polynomial::negate() {
    for(int i = 0; i < monos.size(); i++)
    {
        monos[i].coef.flipSign();
    }
}

void Polynomial::clear() {
    monos.clear();
    totalPower=0;
}

void Polynomial::multByNumber(Number &n) {
    for(int i = 0; i < monos.size(); i++)
    {
        monos[i].coef*=n;
    }
}
