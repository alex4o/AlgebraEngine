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

using namespace std;
#define DEBUG true
#include "Generator.hpp"
#include "SPolynomial.hpp"
#include "7klas.hpp"



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


    while(true)
    {
        int cNums, sum;
        cin>>cNums>>sum;
        int arr[cNums];
        createListOfInts(arr, cNums, sum, &jesus);
        for(int i = 0; i < cNums; i++) cout<<arr[i]<<" ";
        cout<<endl;
        getchar();
    }

	/*cout<<"Aide na zadachite!\n";

    Generator gen;

    gen.descriptor.pFraction=100;
    gen.descriptor.pNatural=0;
    gen.descriptor.pIrational=0;
    gen.descriptor.upHigh=20;
    gen.descriptor.upLow=1;
    gen.descriptor.downLow=2;
    gen.descriptor.downHigh=20;

    SPolynomial a, b;
    a.letter='x';
    b.letter='x';
    a.power=1;
    a.coef[0]=-2;
    a.coef[1]=1;
    //a.coef[2]=2;

    b.power=1;
    b.coef[0]=0;
    b.coef[1]=2;

    a.print();
    cout<<endl;
    b.print();
    cout<<endl;

    SPolynomial c= a*b;
    c.letter='x';
    c.print();


    /*while(true)
    {

        Polynomial c = gen.generate(4, 'x');
        c.print();
        cout<<"\n";
        getchar();

    }*/

}
