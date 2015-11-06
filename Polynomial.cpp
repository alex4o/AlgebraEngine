#include "Polynomial.hpp"
#include "Debug.hpp"

using namespace std;

Polynomial operator+(const Polynomial &p1, const Polynomial &p2) {
    int pow = 0; //Събирането се осъществява по алгоритъма за сливане на 2
    std::vector<Monomial> v; //сортирани масива
                             //гарантирано е, че двата полинома са сортирани
    int lim1 = p1.monos.size();
    int lim2 = p2.monos.size();
    int idx1 = 0, idx2 = 0;

    while (idx1 < lim1 && idx2 < lim2) {
        if(p1.monos[idx1]==p2.monos[idx2]) //Ако двата едночелна са еднакви, коефициентите им се сумират
        {                                  //И двата индекса се увеличват
            Number nc = p1.monos[idx1].coef + p2.monos[idx2].coef; //А резултата се добавя към полинома
                                                                   //Ако е различен от 0
            if(nc.null==false)
            {
                Monomial c(nc, p1.monos[idx1].simples);
                v.push_back(c);
            }
            idx1++;
            idx2++;
        }
        else if(p1.monos[idx1]>p2.monos[idx2]) //Ако единия многочлен е по-голям от другия, то тогава
        {                                     //само той се добавя към резултата
            v.push_back(p1.monos[idx1]);
            idx1++;
        }
        else
        {
            v.push_back(p2.monos[idx2]);
            idx2++;
        }
    }
    while(idx1<lim1) v.push_back(p1.monos[idx1++]); //Добавят се всички останали едночлени
    while(idx2<lim2) v.push_back(p2.monos[idx2++]); //Само един от тези цикли може да се изпълни

    Polynomial result(v, v[0].totalPower);

    return result;
}

Polynomial multByMono(const Polynomial &p, const Monomial &m)
{  //Функцията се обасянва сама - умножава целия полином по едночлен
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
    //Реализиран е стадартния алгоритъм за умножение (със сложност N^2 за числа)
    for(int i = 1; i < p2.monos.size(); i++) // Няма смисъл от асимптоматично по-добри алгоритми, защото за
    {                                        // практическите стойности те ще са всъщност по-бавни
        result = result+multByMono(p1, p2.monos[i]);
    }

    return result;
}

Polynomial pow(Polynomial p, int num)
{ //Функция за вдигане на полином на степен
    Polynomial result(Number(1));
    Polynomial tmp = p;
 //Използва се алгоритъм за бърво вдигане на степен чрез степени на 2
    int idx = 1;
    while(idx<=num)
    {
        if(num&idx)  result = result*tmp;
        idx<<=1;
        tmp = tmp*tmp;
    }
 //Сложността е log N
    return result;
}

Polynomial pow(Polynomial p, Number num)
{ //Функция "мост". За в бъдеще може да има и други функции
    if(num.isNatural()) return pow(p, num.fraction.up);
    else return Polynomial();
}

void Polynomial::negate() { //Тази функция се обяснява сама
    for(int i = 0; i < monos.size(); i++)
    {
        monos[i].coef*=-1;
    }
}

void Polynomial::clear() { //И тази също
    monos.clear();
    totalPower=0;
}

void Polynomial::multByNumber(Number &n) { //И тази
    for(int i = 0; i < monos.size(); i++)
    {
        monos[i].coef*=n;
    }
}
