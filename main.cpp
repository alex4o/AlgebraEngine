/*
Статус на проекта: Pre-Alpha
Последен ъпдейт: 2014.11.30 18:45

Име на този модул: Algebra Engine
Описание: Това е основата на проекта, отговаряща за алгебрични операции

Features(направени):
- действия с числа(не много тествани, но мисля че няма грешки) - Fraction;Number
- прости едночлени (от типа х^2)
    - те са просто char(буква) и int(степен)
    - имат оператори за сравнение
- едночлени
    - имат коефицент от клас Number
    - поддържат само умножение, но то стига(засега)
    - имат вход от низ
    - имат оператори за сравнение
    - имат оператор за равенство
- многочлени
    - събиране    //Направени след няколко часа търсене и оправяне
    - умножение   //на грешки и няколко пренаписвания на фукции и оператори
    - конструктор със низ

TO DO списък:

Среден приоритет:

- вход на Number от низ
- изход на Number

Нисък приоритет:
- support на ирационални числа в Number
- Number степенни показатели в Simple(може би ненужно)

Изпълнени:

----На 2014.12.02----
- вход на полиноми от низ

----На 2014.11.30----
Оправи събирането на полиноми
Погледни отново операторите за сравнение на едночлени
Евентуално напиши глупава версия
---------------------


Бележки:
- добре е да се ползва if(DEBUG) { .... } за да се избегне постоянното слагане и триене на код
*/

#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

using namespace std;
#define DEBUG true
#include "Generator.hpp"

int parse(string s)
{
    int n = 0;
    for(int i = 0; i < s.size(); i++)
    {
        n*=10;
        n+=s[i]-'0';
    }
    return n;
}

int main()
{
    Polynomial p("5x3 + 3x2 + 2y");
    stringstream ss;
    p.print(ss);
    //cout<<ss.str();

    RNJ jesus;

    ExpressionDescriptor ed;
    ed.minTerms=1;
    ed.maxTerms=3;

    ed.factored=false;
    ed.letters="abc";

    ed.minLetters=2;
    ed.maxLetters=3;

    ed.cf.pNatural=100;
    ed.cf.pNegative=50;
    ed.cf.pIrational=0;
    ed.cf.pRational=0;
    ed.cf.upHigh=7;
    ed.cf.upLow=1;

    ed.transformCF.pNatural=100;
    ed.transformCF.pIrational=0;
    ed.transformCF.pRational=0;
    ed.transformCF.upHigh=10;
    ed.transformCF.upLow=1;

    ed.minSubTerm=1;
    ed.maxSubTerm=2;

    ed.maxPow=2;

    Expression e1, e2;

    createEquivalentExpressions(e1, e2, ed);

    stringstream ss1, ss2;

    cout<<"Filling streams!\n";
    e1.print(ss1);
    cout<<"e1 done!\n";
    e2.print(ss2);
    cout<<"e2 done!\n";
    cout<<ss1.str()<<endl<<ss2.str();
}
