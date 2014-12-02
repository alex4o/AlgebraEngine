#include "Simple.hpp"


bool isNumeric(char c) {
    return c>='0' and c<='9';
}

Simple::Simple(char c, int p) //Този конструктор сам се обяснява
{
    letter=c;
    pow=p;
}

Simple::Simple(std::string s, int* idx) //Този е малко по-интересен
{                          //Приема, че на позиция idx има буква
    letter=s[*idx];        //тя ще е буквата на простия едночлен
    //цифрите след тази буква образуват степента
    (*idx)++;
    int n = 0;
    while(isNumeric(s[*idx]))
    {
        n*=10;
        n+=s[*idx]-'0';
        (*idx)++;
    }

    if(n)pow=n;
    else pow=1;  //Накрая idx сочи следващата буква в низа

}

bool operator<(Simple &s1, Simple &s2) //Няма как да минем без това
{
    return s1.letter>s2.letter;
}

bool operator>(Simple &s1, Simple &s2)
{
    return s1.letter<s2.letter;
}



bool cmpSimple(Simple s1, Simple s2) {
    return s1>s2;
}