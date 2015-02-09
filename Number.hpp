#ifndef Number_h
#define Number_h

#include "Fraction.hpp"
#include <vector>
#include <string>

#define natural 0x1
#define rational 0x2

class Number          //Класа за "математическо число"
{                     //В момента поддържа само рационални числа, но в бъдеще ще трябва да поддържа и корени
public:               //Което може да е леко гадно, но само леко(надявам се)

    bool null; //ако числото е 0. Оптимизации
    char type; //Побитово пазим типа на числото
    Fraction fraction; //Дробта, която представлява числото - ако е естествено, знаменателя е 1

    std::vector<Number> roots;      //Ирационалната част
    std::vector<Fraction> root_pow; //за бъдеще

    Number();

    Number(int n);

    Number(int _up, int _down);

    /*Number(Number root, Fraction pow)  //А това е конструктора за ирационални числа
    {                                    //Трябва се оправи в бъдеще
        type=0;
        null=false;
        roots.push_back(root);
        root_pow.push_back(pow);
        fraction.up=0;
        fraction.down=1;
    }*/

    bool isNatural() const     //Тези 2 функции се обясняват сами
    {
        return type&natural;
    }

    bool isRational() const
    {
        return type&rational;
    }

    void operator+=(const Number &n1);
    void operator-=(const Number &n1);

    bool operator==(int k)
    {
        if(isNatural()) return fraction.up==k;
        return false;
    }

    bool operator==(const Number& n1)
    {
        if(null and n1.null) return true;
        return type==n1.type and fraction.up==n1.fraction.up and fraction.down==n1.fraction.down;
    }

    bool operator!=(int k)
    {
        if(isNatural()) return fraction.up!=k;
        return true;
    }

    void print() const;
};

Number operator+(const Number &n1, const Number &n2);
Number operator-(const Number &n1, const Number &n2);
Number operator*(const Number &n1, const Number &n2);
Number operator/(const Number &n1, const Number &n2);



Number parseNum(std::string s);
#endif