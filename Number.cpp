#include <iostream>
#include "Number.hpp"

using namespace std;

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

Number::Number() //Стандартен конструктор. Нулира по образец на C#
{
    null=true;
    fraction.up=0;
    fraction.down=1;
    type= natural | rational;
}

Number::Number(int n) //Конструктор за естествено число
{
    type = natural | rational; //Задава числото като рационално и естествено
    if( n)null=false;     //тези 3 реда се обясняват сами
    else null=true;
    fraction.down=1;
    fraction.up=n;
}

Number::Number(int _up, int _down) //Конструктор за дроб, работи аналогично на горния
{
    type=rational;

    int g = gcd(_up, _down);
    if(g>1)
    {
        _up/=g;
        _down/=g;
    }

    if(_down==1) type=type | natural; //Така е по-удобно, защото функциите трябва да викат само този конструктор
    if(_up) null=false;
    else null=true;
    fraction.up=_up;
    fraction.down=_down;
}



Number parseNum(string s)
{
    //cout<<"[parse]\n";

    int sign = 1;
    int idx=0;
    bool slash = false;
    if(s[0]=='-')
    {
        idx++;
        sign=-1;
    }
    if(s[0]=='+') idx++;

    Number c;
    c.fraction.up = 0;
    while(s[idx]>='0' and s[idx]<='9')
    {
        c.fraction.up*=10;
        c.fraction.up+=s[idx]-'0';
        idx++;
    }

    if(s[idx]=='/') idx++;
    else if(idx==s.size())
    {
        //cout<<"\t returning natural\n";
        c.fraction.up*=sign;
        c.fraction.down=1;
        c.type= natural | rational;
        c.null=false;
        return c;
    }

    c.fraction.down=0;
    while(s[idx]>='0' and s[idx]<='9')
    {
        c.fraction.down*=10;
        c.fraction.down+=s[idx]-'0';
        idx++;
    }

    if(c.fraction.down==0)
    {
        //cout<<"\t returning invalid(x/0)\n";
        return Number();
    }
    int g = gcd(c.fraction.up, c.fraction.down);
    if(g!=1)
    {
        c.fraction.up/=g;
        c.fraction.down/=g;
    }

    c.fraction.up*=sign;

    if(c.fraction.up==0)
    {
        //cout<<"\t returning 0\n";
        c.type=natural;
        c.null=true;
        return c;
    }
    if(c.fraction.down==1)
    {
        //cout<<"\t returning natural(x/1)\n";
        c.type=natural || rational;
        c.null=false;
        return c;
    }

    //cout<<"\t returning natural\n";
    c.type= rational;
    c.null=false;
    return c;
}

void Number::print(bool ignoreOne, bool ignoreSign, stringstream& ss)
{
    bool negative = false;
    if(fraction.up<0) negative=true;

    if(ignoreSign and negative) fraction.up*=-1;
    if(ignoreOne and fraction.up==1 and !negative) return;
    if(isNatural()) ss<<fraction.up;
    else if(isRational())
    {
        if(negative and !ignoreSign)ss<<"-\\frac{"<<-fraction.up<<"}{"<<fraction.down<<"}";
    }
    if(ignoreSign and negative) fraction.up*=-1;
    //cout<<" ["<<null<<isRational()<<isNatural()<<"] ";
    //cout<<fraction.up<<"/"<<fraction.down;
}


Number operator+(const Number &n1, const Number &n2) //Събиране на 2 числа
{
    /*cout<<"[Sum] ";
    n1.print();
    cout<<" and ";
    n2.print();
    cout<<endl;*/
    if(n1.null and n2.null) //Оптимизации ако 1 или 2 числа са 0
    {
        //cout<<"\t both are null\n";
        return Number();
    }
    if(n1.null and !n2.null) return n2;
    if(n2.null and !n1.null) return n1;

    if(n1.isNatural() and n2.isNatural()) //Ако и двете числа са естествени
    {
        //cout<<"\t both are natural\n";
        return Number(n1.fraction.up+n2.fraction.up);
    }
    if(n1.isRational() and n2.isRational()) //Ако и двете са рационални
    {
        //cout<<"\t both are fractions\n";
        int u = n1.fraction.up*n2.fraction.down+n2.fraction.up*n1.fraction.down;
        int d = n1.fraction.down*n2.fraction.down;
        //cout<<"\t raw: "<<u<<"/"<<d<<endl;
        int g = gcd(u,d);
        u/=g;
        d/=g;
        return Number(u,d); //Ето за това говорех в този тип конструктор. Понякога d=1 но няма нужда да правим проверка тук
    }
    //cout<<"\t we shouldn't be here\n";
    return Number(); //Часта за ирационални числа
}

void Number::operator+=(const Number &n1) //Добавяне
{
    /*cout<<"Old: ";
    print();
    cout<<"\nAdding: ";
    n1.print();*/

    if(n1.null) return;

    if(n1.isRational()) //Ако и двете числа са естествени
    {
        int nu = fraction.up*n1.fraction.down + n1.fraction.up*fraction.down;
        int nd = fraction.down*n1.fraction.down;

        if(nd<0) nu*=-1;

        int g = gcd(nu, nd);
        fraction.up = nu/g;
        fraction.down = nd/g;
        fraction.up=nu;
        fraction.down=nd;
    }

    null=false;

    /*cout<<"\nResult: ";
    print();*/

    //cout<<"\t we shouldn't be here\n";
    return; //Часта за ирационални числа
}

void Number::operator-=(const Number &n1) //Добавяне
{
    /*cout<<"[Sum] ";
    n1.print();
    cout<<" and ";
    n2.print();
    cout<<endl;*/
    if(n1.null) return;

    if(n1.isRational()) //Ако и двете числа са естествени
    {
        int nu = fraction.up*n1.fraction.down - n1.fraction.up*fraction.down;
        int nd = fraction.down*n1.fraction.down;

        if(nd<0) nu*=-1;

        int g = gcd(nu, nd);
        fraction.up = nu/g;
        fraction.down = nd/g;
        fraction.up=nu;
        fraction.down=nd;
    }

    //cout<<"\t we shouldn't be here\n";
    return; //Часта за ирационални числа
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
    //std::cout<<"\t\t----[num*] "<<n1.fraction.up<<"/"<<n1.fraction.down<<" * "<<n2.fraction.up<<"/"<<n2.fraction.down<<" = "<<u<<"/"<<d<<std::endl;
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

    if(d<0)
    {
        d*=-1;
        u*=-1;
    }

    return Number(u, d);
}
