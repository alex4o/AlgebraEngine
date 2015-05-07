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
    ExpressionDescriptor ed;
    ed.minTerms=2;
    ed.maxTerms=3;

    ed.factored=false;
    ed.letters[0]='a';
    ed.letters[1]='b';
    ed.letters[2]='c';
    ed.cLetters=1;

    ed.minLetters=1;
    ed.maxLetters=2;

    ed.cf.pNatural=100;
    ed.cf.pNegative=40;
    ed.cf.pIrational=0;
    ed.cf.pRational=0;
    ed.cf.upHigh=3;
    ed.cf.upLow=1;
    ed.cf.downHigh=5;
    ed.cf.downLow=1;

    ed.transformCF.pNatural=100;
    ed.transformCF.pIrational=0;
    ed.transformCF.pRational=0;
    ed.transformCF.upHigh=5;
    ed.transformCF.upLow=1;
    ed.transformCF.downHigh=7;
    ed.transformCF.downLow=1;
    ed.transformCF.pNegative=50;

    ed.minSubTerm=1;
    ed.maxSubTerm=2;

    ed.maxPow=2;


    while(true)
    {
        MultiResult mr = getExpressions(ed, 10);
        for(int i = 0; i < mr.count; i++)
        {
            cout<<mr.ptrProblem[i]<<endl;
            cout<<mr.ptrSolution[i]<<endl;
            cout<<"-----\n";
        }


        free(mr.problem);
        free(mr.solution);
        getchar();
    }

}
