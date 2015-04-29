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
#include <stdlib.h>

using namespace std;
#define DEBUG true
#include "Equation.hpp"
#include "Expression.hpp"
#include "ExpressionDescriptor.hpp"
#include "Generator.hpp"
#include "Interface.hpp"
#include "Inequation.hpp"

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
    InequationDescriptor id;
    id.minTerms=3;
    id.maxTerms=3;

    id.letter = 'x';

    id.cf.pNatural=100;
    id.cf.pNegative=50;
    id.cf.pIrational=0;
    id.cf.pRational=0;
    id.cf.upHigh=3;
    id.cf.upLow=1;
    id.cf.downHigh=10;
    id.cf.downLow=1;

    id.transformCF.pNatural=100;
    id.transformCF.pIrational=0;
    id.transformCF.pRational=0;
    id.transformCF.upHigh=5;
    id.transformCF.upLow=1;
    id.transformCF.downHigh=7;
    id.transformCF.downLow=1;
    id.transformCF.pNegative=50;

    id.nice=true;

    id.rd.pNatural=0;
    id.rd.pNegative=50;
    id.rd.pIrational=0;
    id.rd.pFraction=100;
    id.rd.upHigh=3;
    id.rd.upLow=1;
    id.rd.downHigh=10;
    id.rd.downLow=1;

    while(true)
    {
        Inequation ineq;
        ineq.create(id);

        ineq.addTerm(1);
        ineq.multiplyByNumber();

        stringstream ss1, ss2;
        ineq.print(ss1);
        ineq.printRoots(ss2);

        cout<<ss1.str()<<endl;
        cout<<ss2.str()<<endl;
        getchar();
    }

}
