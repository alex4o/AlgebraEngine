#include "Number.hpp"

Number::Number() //Стандартен конструктор. Нулира по образец на C#
{
    null=true;
}

Number::Number(int n) //Конструктор за естествено число
{
    type = natural || rational; //Задава числото като рационално и естествено
    if( n)null=false;     //тези 3 реда се обясняват сами
    else null=true;
    fraction.down=1;
    fraction.up=n;
}

Number::Number(int _up, int _down) //Конструктор за дроб, работи аналогично на горния
{
    type=rational;
    if(_down==1) type=type || natural; //Така е по-удобно, защото функциите трябва да викат само този конструктор
    if(_up) null=false;
    else null=true;
    fraction.up=_up;
    fraction.down=_down;
}

int gcd ( int a, int b ) //Само се обяснява
{
    if(a<0) a=-a;
    if(b<0) b=-b;
    int c;
    while ( a != 0 )
    {
        c = a;
        a = b%a;
        b = c;
    }
    return b;
}

Number operator+(const Number &n1, const Number &n2) //Събиране на 2 числа
{
    if(n1.null and n2.null) //Оптимизации ако 1 или 2 числа са 0
    {
        return Number();
    }
    if(n1.null and !n2.null) return n2;
    if(n2.null and !n1.null) return n1;

    if(n1.isNatural() and n2.isNatural()) //Ако и двете числа са естествени
    {
        return Number(n1.fraction.up+n2.fraction.up);
    }
    if(n1.isRational() and n2.isRational()) //Ако и двете са рационални
    {
        int u = n1.fraction.up*n2.fraction.down+n2.fraction.up*n1.fraction.down;
        int d = n1.fraction.down*n2.fraction.down;
        int g = gcd(u,d);
        u/=g;
        d/=g;
        return Number(u,d); //Ето за това говорех в този тип конструктор. Понякога d=1 но няма нужда да правим проверка тук
    }

    return Number(); //Часта за ирационални числа
}

Number operator-(const Number &n1, const Number &n2) //Изваждането, всичко е аналогично на събирането
{
    if(n1.null and n2.null)
    {
        return Number();
    }
    if(n1.null and !n2.null) return Number(-n2.fraction.up, n2.fraction.down);
    if(n2.null and !n1.null) return n1;

    if(n1.isNatural() and n2.isNatural())
    {
        return Number(n1.fraction.up-n2.fraction.up);
    }
    if(n1.isRational() and n2.isRational())
    {
        int u = n1.fraction.up*n2.fraction.down - n2.fraction.up*n1.fraction.down;
        int d = n1.fraction.down*n2.fraction.down;
        int g = gcd(u,d);
        u/=g;
        d/=g;
        Number result;
        return Number(u, d);
    }

    return Number();
}

Number operator*(const Number &n1, const Number &n2) //Умножението
{
    if(n1.null or n2.null) return Number(); //Оптимизации с 0
    int u = n1.fraction.up*n2.fraction.up; //Доста по-просто от събирането
    int d = n1.fraction.down*n2.fraction.down; //За разлика от събирането, тук дори не е заделено място за
    int g = gcd(u, d);                         //ирационални числа
    u/=g;
    d/=g;
    return Number(u, d);
}

Number operator/(const Number &n1, const Number &n2) //Делението, аналогично на умножението
{
    if(n1.null or n2.null) return Number();
    int u = n1.fraction.up*n2.fraction.down;
    int d = n1.fraction.down*n2.fraction.up;
    int g = gcd(u, d);
    u/=g;
    d/=g;
    return Number(u, d);
}