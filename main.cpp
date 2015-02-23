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
    RNJ jesus;
    
    RootDescriptor rd;
    rd.pNatural=100;
    rd.pFraction=0;
    rd.pIrational=0;
    rd.pNegative=50;
    rd.upHigh=5;
    rd.upLow=1;
    rd.downLow=1;
    rd.downHigh=10;

    while(true)
    {
        stringstream ss, ss2;

        Equation eq;
        eq.create(2, rd, true);

        eq.print(ss);
        cout<<"original: "<<ss.str()<<endl;;

        eq.addTerm(2, true);
        eq.addTerm(2, true);



        eq.print(ss2);

        cout<<ss2.str()<<endl;

        getchar();
    }
}
