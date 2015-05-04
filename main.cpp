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
    EquationDescriptor ed;
    ed.minTerms=3;
    ed.maxTerms=3;

    ed.letter = 'x';

    ed.cd.pNatural=100;
    ed.cd.pNegative=50;
    ed.cd.pIrational=0;
    ed.cd.pIrational=0;
    ed.cd.upHigh=3;
    ed.cd.upLow=1;
    ed.cd.downHigh=10;
    ed.cd.downLow=1;

    ed.transformCF.pNatural=100;
    ed.transformCF.pIrational=0;
    ed.transformCF.pRational=0;
    ed.transformCF.upHigh=5;
    ed.transformCF.upLow=1;
    ed.transformCF.downHigh=7;
    ed.transformCF.downLow=1;
    ed.transformCF.pNegative=50;

    ed.nice=true;

    ed.rd.pNatural=0;
    ed.rd.pNegative=50;
    ed.rd.pIrational=0;
    ed.rd.pFraction=100;
    ed.rd.upHigh=3;
    ed.rd.upLow=1;
    ed.rd.downHigh=10;
    ed.rd.downLow=1;

    ed.type=2;
    ed.power=2;
    ed.maxTermPower=2;

    Generator gen;

    while(true)
    {
        Equation eq = gen.generateEquation(ed);

        stringstream ss1, ss2;
        eq.print(ss1);
        eq.printRoots(ss2);

        cout<<ss1.str()<<endl;
        cout<<ss2.str()<<endl;
        getchar();
    }

}
