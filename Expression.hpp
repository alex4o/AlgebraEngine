#ifndef ExpH
#define ExpH

#include "Polynomial.hpp"
#include <vector>

using namespace std;



class Term
{ //това, което на сайта е наречено "скоби"
public: //представлява произведение на полиноми с коефициент пред него
    vector<Polynomial> polys;
    vector<Number> powers;
    Number coef;

    bool isMod; //все още WIP, показва дали "скобата" е модул

    Term()
    {
        isMod=false;
    }

    Term(Number c)
    {
        coef=c;
        isMod=false;
    }

    Term(Polynomial pol, Number n)
    {
        polys.push_back(pol);
        coef = n;
        isMod=false;
    }

    Polynomial toPoly() //важна функция, която пресмята стойността на скобата в нормален вид
    {
        if(polys.empty()) return Polynomial(coef);
        Polynomial result = pow(polys[0], powers[0]);
        for(int i = 1; i < polys.size(); i++)
        {
            result = result * pow(polys[i], powers[i]);
        }

        result.multByNumber(coef);
        return result;
    }

    void print()
    {
        stringstream ss;
        coef.print(false, false, ss);
        cout<<ss.str();
        ss.str("");
        for(int i = 0; i < polys.size(); i++)
        {
            cout<<"(";
            polys[i].print(ss);
            cout<<ss.str()<<")^"<<powers[i].fraction.up;
        }
    }
};

class Expression
{ //Това е клас за израз, който не е в нормлен вид
public:
    Polynomial free; //Съдържа полином и "скоби"
    vector<Term> terms;

    Expression()
    {

    }

    Expression(Number n)
    {
        free = Polynomial(n);
    }

    Expression(char letter)
    {
        Monomial m(Number(1), letter);
        free.monos.push_back(m);
    }

    Expression(Number coef, char letter)
    {
        Monomial m(coef, letter);
        free.monos.push_back(m);
    }

    void addTerm(Term& t, bool add)
    { //Тази функция прави добавянето на скоби лесно
        if(add) //В единия случай се добавя стойността на скобата
        {
            Polynomial tmp = t.toPoly();

            free = free + tmp;
        }
        else //а в другия самата тя
        {
            terms.push_back(t);
        }
    }

    void multByNum(Number n)
    { //Тази функция се обяснява сама. Засега не се ползва
        free = multByMono(free, Monomial(n));
        for(int i = 0; i < terms.size(); i++)
        {
            terms[i].coef = terms[i].coef*n;
        }
    }

    void print(stringstream& ss)
    { //Това е функцията, в която се случва основната част от принтирането
        if(terms.size()>0)
        {
            terms[0].coef.print(true, false, ss); //Това е специален случай за първият елемент
            if(terms[0].isMod) ss<<'|'; //за него числото се изкарва нормално, доката при всички останали
                                       //се принтира по по-специален начин
            bool skip = terms[0].isMod && terms[0].polys.size()==1;
                    //Също така тук се отчита и възможността скобата да е модул
            for(int j = 0; j < terms[0].polys.size(); j++)
            {
                if(!skip)ss<<"("; //в такъв случай това се припуска
                terms[0].polys[j].print(ss);
                if(!skip)ss<<")";

                if(terms[0].powers[j]!=1)
                {
                    ss<<"^";
                    terms[0].powers[j].print(true, false, ss);
                }

            }
            if(terms[0].isMod) ss<<'|'; //и се слага това

            for(int i = 1; i < terms.size(); i++) //аналогично на горния код
            {
                ss<<' '<<terms[i].coef.getSign()<<' '; //тук числото и знака се разделят с интервал

                terms[i].coef.print(true, true, ss);
                if(terms[i].isMod) ss<<'|';

                bool skip = terms[i].isMod && terms[i].polys.size()==1;

                for(int j = 0; j < terms[i].polys.size(); j++)
                {
                    if(!skip)ss<<"(";
                    terms[i].polys[j].print(ss);
                    if(!skip)ss<<")";

                    if(terms[i].powers[j]!=1)
                    {
                        ss<<"^";
                        terms[i].powers[j].print(true, false, ss);
                    }

                }
                if(terms[i].isMod) ss<<'|';
            }
        }

        if(!free.empty()) //След принтирането на скобите накрая се показва и полинома
        {
            if(terms.empty()) free.print(ss);
            else free.print(ss, true);
        }

        if(terms.empty() && free.empty()) ss<<'0';
    }

    int getLen()
    { //Това се използва за относително балансиране на двете страни на уравнение, например.
        return terms.size() + (free.empty()==false);
    }
};

#endif